# HTMX WEBSITE REQUIREMENTS AND DESIGN DECISIONS

# Pages

**REQ-HTMX-100:** The webserver will be divided in pages. Some pages will be generic between projects. Below are the pages mentioned for a particular project:

- Application specific pages
- Configuration: this page is different per application, but the page should exist and show the configuration of the project.
- Status: this page is equal for all applications, shows the status of all slaves and the master.
- Initialization: this page is equal for all applications, shows the initialization process of the slaves and master.
- Security: this page is equal for all applications, shows the security settings and allows to change the ESP-NOW key.
- Logging: this page is equal for all applications, shows the logs of the system.
- Firmware: this page is equal for all applications, shows the firmware versions of all slaves and the master.
- Manual: this page is different per application, but the page should exist and show the manual of the project.

**Rationale:** The structure needs to be clear for users and developers. Some pages are generic and can be reused across projects, while others are application specific and need to be customized.
**Alternative considered:** A single page with all information and configuration options — rejected, would be too cluttered and less user-friendly. Only application specific pages without generic pages — rejected, would make it harder for users to find common information and configuration options across different projects.

**REQ-HTMX-110:** Header: The header of each page shall show the name of the project, the version number, and for non Home pages,a Home button and a sub title. For multi level pages, a Back button shall be shown in the header to go back to the previous page. The header is consistent across all pages.<br/>
**Rationale:** A consistent header provides a clear structure and navigation for users across all pages. The Home button allows users to easily return to the main page, while the Back button provides a way to navigate back through multi-level pages without losing context.<br/>
**Alternative considered:** No header or inconsistent headers across pages — rejected, would lead to a confusing

# Configuration

**REQ-HTMX-250:** The configuration page has a Load and Save button. Each changed setting is send to the webserver and takes in effect immediately. When the Load button is used, the website settings are overwritten. When the Save button is pressed, all settings are stored in NVS. For a successful Load or Save, the button changes temporarily in Loaded! or Saved!. In case of an error, the button changes to Error! temporarily. In case of a specific setting cannot be changed, the label of the setting will be temporarily changed into Error!.<br/>
**Rationale:** Provides a clear and immediate feedback to the user about the success or failure of their actions, improving the user experience and making it easier to understand the state of the system. Immediate effect of changes allows for quick testing and iteration without needing to reload the page or restart the system.<br/>
**Alternative considered:** No feedback on Load/Save actions — rejected, would leave users uncertain about whether their actions were successful. Changes only take effect after a page reload or system restart — rejected, would slow down the configuration process and make it less user-friendly.

**REQ-HTMX-260:** The configuration page shall have its configurations in different panes, named according to the category of the settings. Each pane can be expanded or collapsed to show or hide the settings within it.<br/>
**Rationale:** Organizing settings into categorized panes improves the user experience by reducing clutter and making it easier for users to find and focus on specific settings. The ability to expand or collapse panes allows users to customize their view and focus on the settings that are relevant to them at any given time.<br/>
**Alternative considered:** All settings shown in a single list without categorization or collapsible panes — rejected, would be overwhelming and make it difficult for users to find specific settings, especially as the number of settings grows.

# Status

**REQ-HTMX-300:** The status page shall show the status of all slaves and the master, including their connection status, IP addresses, and any relevant metrics or information specific to the project. The following information is shown:
- Node number and name
- Role (Master, , Remote, Slave type)
- Slave sequence number: number of the slave for that type; only for slaves
- Status: OK/NOK
- Last communication: time since last message received from that slave
- Uptime: time since the node booted
- Firmware version: the firmware version of the node
- Configuration version: the version of the configuration that the node is using, to detect if the node has an outdated configuration after a change
- MAC address: the MAC address of the node, to detect if the node is recognized by the master and for routing purposes
- IP address: the IP address of the node, to detect if the node is connected to the network and for routing purposes (only for Webserver slaves and remotes)
**Rationale:** Providing a comprehensive status page allows users to easily monitor the health and performance of the system, quickly identify any issues, and understand the current state of all components. This is essential for effective troubleshooting and maintenance.<br/>
**Alternative considered:** No status page or a very minimal status page with limited information — rejected, would make it harder for users to monitor the system and identify issues, leading to a poorer user experience and more difficult maintenance. 

# Initialization

**REQ-HTMX-350:** The initialization page shall shows the MAC address of all nodes, a way to change the MAC addresses and a Save button. Also, the system can be restarted here.<br/>
**Rationale:** The initialization page provides a clear overview of all nodes in the system and their MAC addresses, which are crucial for routing and communication. Allowing users to change MAC addresses and save them provides flexibility in network configuration without needing to modify firmware. The ability to restart the system from this page allows users to easily apply changes and troubleshoot issues.<br/>
**Alternative considered:** No initialization page or a very minimal initialization page without MAC address management — rejected, would make it harder for users to manage their network configuration and apply changes, leading to a less flexible and more difficult to maintain system.

# Security 

**REQ-HTMX-400:** The security page shall show the current ESP-NOW security key and allow users to change it. When the key is changed, it is sent to the master to be spread to all slaves.<br/>
**Rationale:** The security page provides users with visibility into the current security settings of the system and allows them to easily update the ESP-NOW security key without needing to modify firmware. Sending the new key to the master for distribution ensures that all nodes in the system are updated with the new key, maintaining secure communication across the network.<br/>
**Alternative considered:** No security page or a security page without the ability to change the ESP-NOW key — rejected, would limit users' ability to manage their security settings and require firmware changes to update the key, which is less user-friendly and reduces security if the firmware is shared.

# Logging 

**REQ-HTMX-450:** The logging page shall show the logs of the system, including messages sent and received, errors, and other relevant events. Logs can be filtered by node, role, or message type.<br/>
**Rationale:** The logging page provides users with valuable insights into the operation of the system, allowing them to monitor communication, identify errors, and understand the behavior of the system. The ability to filter logs by node, role, or message type helps users quickly find relevant information and troubleshoot issues more effectively.<br/>
**Alternative considered:** No logging page or a logging page without filtering options — rejected, would make it harder for users to monitor the system and identify issues, leading to a poorer user experience and more difficult troubleshooting.

# Firmware

**REQ-HTMX-500:** Firmware version of all slaves shall be visible in the Htmx UI.<br/>
**Rationale:** Firmware versions need to be visible for debugging, monitoring, and ensuring compatibility across the system.<br/>
**Alternative considered:** No firmware version visibility — rejected, would make debugging and monitoring more difficult.

# ERROR HANDLING

**REQ-HTMX-700:** When GET/POST messages do not succeed, an error is shown (briefly). For buttons the text will briefly turn red with 'Error' text.<br/>
**Rationale:** Provides immediate feedback to the user about the failure of their action, allowing them to understand that something went wrong and take corrective action if needed. This improves the user experience and helps prevent confusion or frustration when actions do not succeed.<br/>
**Alternative considered:** No error feedback on failed actions — rejected, would leave users uncertain about whether their actions were successful and could lead to confusion or frustration when things do not work as expected.




# Software Organization

# Testing

# Hardware
