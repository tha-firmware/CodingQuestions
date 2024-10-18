This program is designed to run on the GCC compiler obtained via Windows MinGW. It uses the <window.h> include for semaphores and thread creation. You can also execute the build .exe file.

During my meeting with Matt, I presented a conceptual approach for executing worker items on a different thread, making the producer and consumer asynchronous. This code is the complete implementation of the question Matt asked me. It has been written to execute gracefully.
