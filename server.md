## Block server
Block server code
```c++
void AbstractServer::run() {
  for (;;) {
    tcp::socket socket{io_context};
    acpt.accept(socket);
    std::thread(&AbstractServer::session, this, std::move(socket)).detach();
  }
}
```
How this work
- This is blocking synchronous I/O, not asynchronous. **acpt.accept(socket)** is a blocking call that waits until a new connection is ready.
- Since this is synchronous, **boost::asio::io_context::run()** isn't needed.
- **io_context** is only being used to construct the socket and acceptor, but it's not used to run any async operations or event loops.

Downsides of this pattern
- Blocking accept
  - The accept() call blocks the thread completely.
  - Only one connection can be accepted at a time.
- Unbounded threads
  - Each session runs in a detached thread.
  - If many clients connect, you'll quickly spawn a huge number of threads — not scalable.
- No control or cleanup
  - Detached threads are hard to manage and clean up.
  - If session() throws, it could crash silently.
- Wasted potential
  - You’re using boost::asio but not taking advantage of its async power (e.g. async_accept, async_read).

## Better approach: Async server + io_context.run()
Code
```c++
void AbstractServer::startAccept() {
    auto socket = std::make_shared<tcp::socket>(io_context);
    acpt.async_accept(*socket, [this, socket](boost::system::error_code ec) {
        if (!ec) {
            std::thread(&AbstractServer::session, this, std::move(*socket)).detach();
        }
        startAccept(); // Accept next connection
    });
}

void AbstractServer::run() {
    startAccept();
    io_context.run();  // Start the async event loop
}
```
Now you’re accepting asynchronously.
\
You can also eventually run session() inside a thread pool instead of spawning detached threads.
\
io_context.run() keeps the event loop alive and responsive.
