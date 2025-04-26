import psutil
import pytest
import requests
import subprocess
import time
import json

BASE_URL = 'http://localhost:1999'
FILE_API = '/api/file'

@pytest.fixture(scope="session", autouse=True)
def start_and_stop_program():
    program_name = 'WebApi'

    # Check if the process is already running
    process_running = any(program_name in proc.info['name'] for proc in psutil.process_iter(['pid', 'name']))

    process = None
    if not process_running:
        process = subprocess.Popen(['../build/WebApi'])
        time.sleep(1)

    yield

    if process is not None:
        print("Stopping process...")
        process.terminate()
        process.wait()

# ✅ Utility function (not named test_)
def validate_json_structure(data):
    required_keys = ['Name', 'homeTown', 'formed', 'secretBase', 'active', 'members']
    for key in required_keys:
        assert key in data, f"Missing key: {key}"

    assert isinstance(data['members'], list), "'members' is not a list"

    for member in data['members']:
        for field in ['name', 'age', 'secretIdentity', 'powers']:
            assert field in member, f"Missing field '{field}' in member: {member}"
        assert isinstance(member['powers'], list), f"'powers' is not a list in member: {member}"

# ✅ Actual test
@pytest.mark.order(1)
def test_get_file():
    url = f"{BASE_URL}{FILE_API}"
    response = requests.get(url)

    assert response.status_code == 200, f"Unexpected status code: {response.status_code}"
    assert 'application/octet-stream' in response.headers.get('Content-Type', ''), "Content-Type is not application/octet-stream"

    try:
        data = json.loads(response.content.decode('utf-8'))
    except Exception as e:
        pytest.fail(f"Failed to decode or parse JSON: {e}")

    # ✅ Call helper
    validate_json_structure(data)
