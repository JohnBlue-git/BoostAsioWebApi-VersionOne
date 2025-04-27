import psutil
import pytest
import requests
import subprocess
import os
import time
import json
import io
import tarfile

BASE_URL = 'http://localhost:1999'
FILE_API = '/api/file'
TARBALL_API = '/api/tarball'
TMPFOLDER = '../files/tmp'

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
def parse_to_json(json_bytes):
    # Not work !
    # assert isinstance(json_bytes, bytearray), "Input must be a bytearray object"

    try:
        data = json.loads(json_bytes.decode('utf-8'))
        return data
    except Exception as e:
        pytest.fail(f"Failed to decode or parse JSON: {e}")

# ✅ Utility function (not named test_)
def validate_json_structure(data: dict):
    assert isinstance(data, dict), "Input must be a dictionary or JSON-like object"

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

    # To decode and parse JSON
    data = parse_to_json(response.content)

    # ✅ Call validator
    validate_json_structure(data)

# ✅ Utility function (not named test_)
def is_valid_tarball(byte_stream: io.BytesIO):
    assert isinstance(byte_stream, io.BytesIO), "Input must be a io.BytesIO object"

    # Try listing contents
    try:
        # Save current stream position
        pos = byte_stream.tell()
        with tarfile.open(fileobj=byte_stream, mode="r:*") as tar:
            tar.getmembers()
    except tarfile.TarError:
        # Stop this test
        pytest.fail(f"Invalid tarball: {e}")
    finally:
        # Reset stream position
        byte_stream.seek(pos)

# ✅ Utility function (not named test_)
def extract_tarball(tar_bytes: io.BytesIO):
    assert isinstance(tar_bytes, io.BytesIO), "Input must be a io.BytesIO object"

    try:
        with tarfile.open(fileobj=tar_bytes, mode="r:*") as tar:
            # Look for data.json
            member = next((m for m in tar.getmembers() if m.name.endswith("data.json")), None)
            assert member is not None, "data.json not found in tarball"
            # Extract tarball
            extracted = tar.extractfile(member)
            # Parse to JSON
            json_bytes = extracted.read()
            return json_bytes
    except Exception as e:
        pytest.fail(f"Failed to process tarball or parse JSON: {e}")

@pytest.mark.order(2)
def test_get_tarball():
    url = f"{BASE_URL}{TARBALL_API}"
    response = requests.get(url)

    assert response.status_code == 200, f"Unexpected status code: {response.status_code}"
    assert 'application/x-tar' in response.headers.get('Content-Type', ''), "Content-Type is not application/x-tar"

    # Read tarball from response content
    tar_bytes = io.BytesIO(response.content)
    is_valid_tarball(tar_bytes)
    # The file content to be filled in trough de-compression
    # json_bytes = bytearray()
    json_bytes = extract_tarball(tar_bytes)
    # To decode and parse JSON
    # data = {}
    data = parse_to_json(json_bytes)

    # Call validator
    validate_json_structure(data)

    # Save the content to a file
    with open('data.tar', 'wb') as f:
        f.write(response.content)

def open_tarball():
    assert os.path.isfile('data.tar'), "data.json file not found in the folder"
    with open('data.tar', 'rb') as tar_file:
        tar_bytes = tar_file.read()
        return tar_bytes

def read_file():
    # Check folder exists
    assert os.path.isdir(TMPFOLDER), f"Folder does not exist: {TMPFOLDER}"
    # List files
    files = os.listdir(TMPFOLDER)
    assert files, f"There is no file found in folder: {TMPFOLDER}"
    # Look for data.json file
    data_json_path = os.path.join(TMPFOLDER, 'data.json')
    assert os.path.isfile(data_json_path), "data.json file not found in the folder"
    with open(data_json_path, 'rb') as f:
        file_bytes = f.read()
    assert file_bytes.strip() != "", "data.json is empty"
    return file_bytes

@pytest.mark.order(3)
def test_post_tarball():
    url = f"{BASE_URL}{TARBALL_API}"
    headers = {'Content-Type': 'application/json'}
    # Open the tarball file
    tar_bytes = open_tarball()
    # Send the POST request with the tarball
    response = requests.post(url, data=tar_bytes, headers=headers)

    assert response.status_code == 204, f"Unexpected status code: {response.status_code}"

    # Read file
    file_bytes = read_file()
    # To decode and parse JSON
    # data = {}
    data = parse_to_json(file_bytes)

    # Call validator
    validate_json_structure(data)

def check_files_not_exist():
    # Check folder exists
    assert os.path.isdir(TMPFOLDER), f"Folder does not exist: {TMPFOLDER}"
    # List files
    files = os.listdir(TMPFOLDER)
    assert not files, f"files found in folder: {TMPFOLDER}"

@pytest.mark.order(4)
def test_delete_tarball():
    url = f"{BASE_URL}{TARBALL_API}"
    response = requests.delete(url)

    assert response.status_code == 204, f"Unexpected status code: {response.status_code}"

    # Check tmp folder shall be empty 
    check_files_not_exist()

@pytest.mark.order(5)
def test_delete_tarball():
    # Delete the tarball file after the test
    if os.path.exists('data.tar'):
        os.remove('data.tar')
