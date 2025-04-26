#include <iostream>
#include <thread> // for std::this_thread::sleep_for(std::chrono::seconds(3));
#include <csignal>
#include <unistd.h>
#include <semaphore.h>

#include "router.hpp"
#include "block_accept_server.hpp"
#include "async_accept_server.hpp"

#include "person_service.hpp"
#include "advance_person_service.hpp"
#include "person_controller.hpp"

#include "file_service.hpp"
#include "file_controller.hpp"

#include "tarball_service.hpp"
#include "tarball_controller.hpp"

//
// Fence
//

class Fence {
private:
    static sem_t semaphore;
public:
    static void initSema() {
        sem_init(&semaphore, 0, 0);
    }
    static void waitSignal() {
        sem_wait(&semaphore);
    }
    static void signalHandler(int signum) {
        sem_post(&semaphore);
        sem_destroy(&semaphore);
    }
};
sem_t Fence::semaphore; // Initialize static member

//
// Main
//

int main(void)
{
  try {
    // Create services
    //
    auto personService = std::make_shared<PersonService>();
    auto personController = std::make_shared<PersonController>(personService);
    //
    auto advance_personService = std::make_shared<AdvancePersonService>();
    auto advance_personController = std::make_shared<PersonController>(advance_personService);
    //
    auto fileService= std::make_shared<FileService>();
    auto fileController = std::make_shared<FileController>(fileService);
    //
    auto tarballService= std::make_shared<TarballService>();
    auto tarballController = std::make_shared<TarballController>(tarballService);
    
    // Register routing
    auto router = std::make_shared<Router>();
    //
    router->addRoute("/api/person", personController);
    //
    router->addRoute("/api/advance_person", advance_personController);
    //
    router->addRoute("/api/file", fileController);
    //
    router->addRoute("/api/tarball", tarballController);

    // Create server
#if defined(ASYNC_ACCEPT)
    auto server = AsyncAcceptServer(1999, router);
#elif defined(BLOCK_ACCEPT)
    auto server = BlockAcceptServer(1999, router);
#else
    auto server = BlockAcceptServer(1999, router);
#endif
    server.run();
    std::cout << "Server starting on port " << server.getPort() << std::endl;

    // Stop fence
    Fence::initSema();
    signal(SIGINT, Fence::signalHandler);
    signal(SIGTERM, Fence::signalHandler);
    Fence::waitSignal();

  } catch (std::exception const &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return 0;
}
