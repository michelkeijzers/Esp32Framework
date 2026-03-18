# TODO

# MANUAL SHORT TERM 

- [ RTOS Tasks ] Add a task for handling webserver API requests, separate from the main ESP-NOW message handling task.
- [ Logging ] Add more log messages for debugging and monitoring (e.g. connection status, API calls, errors, etc.).

# MID LONG TERM

## Common WebServer 

- [ ] Status API.
- [ ] Logging API.
- [ ] Security API (view/change ESP-NOW key).
- [ ] Status API (list of nodes with status, last communication time, uptime, firmware version, configuration version).
- [ ] Firmware API (chunked firmware upload with progress and retries).
- [ ] Integration tests for all APIs (above).
- [ ] Frontend pages for all APIs (status, logging, security, firmware).
- [ ] OTA update via Wi-Fi (for webserver itself).
- [ ] OTA update via ESP-NOW (for nodes without Wi-Fi, long term solution).
- [ ] ESP-NOW connection status monitoring (e.g. signal strength, last successful communication time).
- [ ] More detailed status reporting (e.g. per-node logs, performance metrics).
- [ ] Support for multiple webservers (e.g. in larger deployments, with load balancing or redundancy).
- [ ] More advanced security features (e.g. dynamic keys, authentication, etc.).
- [ ] More advanced logging features (e.g. log levels, remote logging, etc.).
- [ ] More advanced error handling (e.g. specific error codes, retry strategies, etc.).
- [ ] More advanced performance optimizations (e.g. message batching, compression, etc.).
- [ ] More advanced frontend features (e.g. real-time updates, custom dashboards, etc.).
- [ ] More advanced API features (e.g. more endpoints, more parameters, etc.).
- [ ] More advanced OTA features (e.g. delta updates, rollback, etc.).
- [ ] More advanced testing (e.g. long term stability testing, security testing, etc.).
- [ ] Add more details to design docs (e.g. architecture diagrams, API specifications, etc.).
- [ ] Add more details to rationale and alternatives for design decisions.
- [ ] Add more details to testing strategy and test cases.
- [ ] Add more details to hardware design (e.g. specific components, connections, etc.).
- [ ] Add more details to security design (e.g. specific encryption algorithms, key management strategies, etc.).
- [ ] Add more details to performance design (e.g. specific optimizations, benchmarks,  etc.).
- [ ] Add more details to error handling design (e.g. specific error codes, retry strategies, etc.).
- [ ] Add more details to software organization (e.g. specific modules, classes, functions, etc.).
- [ ] Add more details to testing strategy (e.g. specific test cases, expected results, etc.).  
- [ ] Add more details to API specifications (e.g. specific endpoints, parameters, responses, etc.).
- [ ] Add more details to frontend design (e.g. specific pages, components, interactions, etc.).
- [ ] Add more details to message specifications (e.g. specific message types, parameters, flows, etc.).
- [ ] Add more details to security design (e.g. specific encryption algorithms, key management strategies, etc.).
- [ ] Add more details to performance design (e.g. specific optimizations, benchmarks,

## Common Website 

- [ ] Home page with navigation to other pages.
- [ ] Status page showing all nodes with status, last communication time, uptime, firmware version, configuration version.
- [ ] Logging page showing system logs with timestamps and sources.
- [ ] Security page for viewing/changing ESP-NOW key.
- [ ] Firmware page for managing firmware versions and OTA updates.
- [ ] Manual page with static HTML content, ready for custom content.
- [ ] Add more details to frontend design (e.g. specific pages, components, interactions, etc.).
- [ ] Add more details to API specifications (e.g. specific endpoints, parameters, responses, etc.).
- [ ] Add more details to design docs (e.g. architecture diagrams, API specifications, etc.).
- [ ] Add more details to rationale and alternatives for design decisions.
- [ ] Add more details to testing strategy and test cases.
- [ ] Add more details to hardware design (e.g. specific components, connections, etc.).
- [ ] Add more details to security design (e.g. specific encryption algorithms, key management strategies, etc.).
- [ ] Add more details to performance design (e.g. specific optimizations, benchmarks, etc.).
- [ ] Add more details to error handling design (e.g. specific error codes, retry strategies, etc.).
- [ ] Add more details to software organization (e.g. specific modules, classes, functions, etc.).
- [ ] Add more details to testing strategy (e.g. specific test cases, expected results, etc.).


# Documentation 

- [ ] Documentation generation (e.g. Doxygen) for codebase.
- [ ] Update design docs with final architecture and API details.
- [ ] Add more diagrams (e.g. sequence diagrams for message flows, component diagrams for software organization).
- [ ] Add more details to testing strategy and test cases.
- [ ] Add more details to hardware requirements and design (e.g. specific pinouts, power requirements, etc.).
- [ ] Add more details to security considerations and design (e.g. key management, attack vectors, etc.).
- [ ] Add more details to performance considerations and design (e.g. expected message rates, latency requirements, etc.).
- [ ] Add more details to error handling design (e.g. specific error codes, retry strategies, etc.).
- [ ] Add more details to software organization (e.g. specific modules, classes, functions, etc.).
- [ ] Add more details to testing strategy (e.g. specific test cases, expected results, etc.).
- [ ] Add more details to hardware design (e.g. specific components, connections, etc.).
- [ ] Add more details to long term plans (e.g. specific features, timelines, etc.).
- [ ] Add more details to rationale and alternatives for design decisions.
- [ ] Add more details to API specifications (e.g. specific endpoints, parameters, responses, etc.).
- [ ] Add more details to frontend design (e.g. specific pages, components, interactions, etc.).
- [ ] Add more details to message specifications (e.g. specific message types, parameters, flows, etc.).
- [ ] Add more details to security design (e.g. specific encryption algorithms, key management strategies, etc.).
- [ ] Add more details to performance design (e.g. specific optimizations, benchmarks,
    etc.).
- [ ] Add more details to error handling design (e.g. specific error codes, retry strategies, etc.).
- [ ] Add more details to software organization (e.g. specific modules, classes, functions, etc.).
- [ ] Add more details to testing strategy (e.g. specific test cases, expected results, etc.).
- [ ] Add more details to hardware design (e.g. specific components, connections, etc

# Testing

- [ ] Add more unit tests for edge cases and error handling.
- [ ] CICD pipeline for running tests on push.
- [ ] Code coverage reporting.
- [ ] Integration tests for webserver and website.
- [ ] Manual testing of frontend and OTA updates.
- [ ] Performance testing under load (e.g. high message rates, multiple nodes, etc.).
- [ ] Security testing (e.g. key management, attack vectors, etc.).
- [ ] Error handling testing (e.g. message loss, node failures, etc.).
- [ ] Usability testing of frontend (e.g. user feedback, navigation, etc.).
- [ ] Long term testing (e.g. stability over time, OTA update reliability, etc.).
- [ ] Hardware testing (e.g. power consumption, range, etc.).
- [ ] Testing of edge cases and failure modes (e.g. Wi-Fi loss, node failures, etc.).
- [ ] Testing of security features (e.g. key changes, encryption, etc.).
- [ ] Testing of performance under load (e.g. high message rates, multiple nodes, etc.).
- [ ] Testing of error handling (e.g. message loss, node failures, etc.).
- [ ] Testing of frontend usability (e.g. user feedback, navigation, etc.).
- [ ] Testing of long term stability (e.g. stability over time, OTA update reliability, etc.).
- [ ] Testing of hardware performance (e.g. power consumption, range, etc.).



## Software Environment / Code 

- [ ] CICD / Github Action for automatic building on push.
- [ ] Code linting and formatting (e.g. clang-format, cpplint).
- [ ] Code coverage reporting for unit tests.
- [ ] Refactor code for better modularity and testability (e.g. dependency injection, interface segregation).
- [ ] Add more comments and documentation in code.
- [ ] Add more logging for debugging and monitoring.
- [ ] Add more error handling and edge case handling in code.
- [ ] Refactor code for better performance and memory usage (e.g. avoid dynamic memory allocation, optimize data structures, etc.).
- [ ] Add more configuration options (e.g. via KConfig) for flexibility.
- [ ] Add more abstraction layers for hardware and software components (e.g. hardware abstraction layer, message handling layer, etc.).
- [ ] Add more unit tests for edge cases and error handling.
- [ ] Add more integration tests for webservers and website.
- [ ] Add more tests for performance under load (e.g. high message rates, multiple nodes, etc.).
- [ ] Add more tests for security features (e.g. key changes, encryption, etc.).
- [ ] Add more tests for error handling (e.g. message loss, node failures, etc.).
- [ ] Add more tests for frontend usability (e.g. user feedback, navigation, etc.).
- [ ] Add more tests for long term stability (e.g. stability over time, OTA update reliability, etc.).
- [ ] Add more tests for hardware performance (e.g. power consumption, range, etc.).
- [ ] Add more tests for edge cases and failure modes (e.g. Wi-Fi loss, node failures, etc.).
- [ ] Add more tests for security features (e.g. key changes, encryption, etc.).
- [ ] Add more tests for performance under load (e.g. high message rates, multiple nodes, etc.).
- [ ] Add more tests for error handling (e.g. message loss, node failures, etc.).
- [ ] Add more tests for frontend usability (e.g. user feedback, navigation, etc.).
- [ ] Add more tests for long term stability (e.g. stability over time, OTA update reliability, etc.).
- [ ] Add more tests for hardware performance (e.g. power consumption, range, etc.).

# LONG TERM

## Common Webserver

### Connection with Master

- [ ] OTA update via ESP-NOW (for nodes without Wi-Fi, long term solution).
- [ ] ESP-NOW connection status monitoring (e.g. signal strength, last successful communication time).
- [ ] More detailed status reporting (e.g. per-node logs, performance metrics).
- [ ] Support for multiple webservers (e.g. in larger deployments, with load balancing or redundancy).
- [ ] More advanced security features (e.g. dynamic keys, authentication, etc.).
- [ ] More advanced logging features (e.g. log levels, remote logging, etc.).  
- [ ] More advanced error handling (e.g. specific error codes, retry strategies, etc.).
- [ ] More advanced performance optimizations (e.g. message batching, compression, etc.).   
- [ ] More advanced frontend features (e.g. real-time updates, custom dashboards, etc.).
- [ ] More advanced API features (e.g. more endpoints, more parameters, etc.).
- [ ] More advanced OTA features (e.g. delta updates, rollback, etc.).
- [ ] More advanced testing (e.g. long term stability testing, security testing, etc.).
