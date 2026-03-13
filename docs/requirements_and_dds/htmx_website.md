# HTMX WEBSITE REQUIREMENTS AND DESIGN DECISIONS

# Pages

## Multiple Pages

**REQ-HTMX-100:** The webserver is divided into multiple pages, with a mix of generic and application-specific content:
	- Application-specific pages
	- Configuration: project-specific configuration options
	- Status: status of all nodes (master and slaves)
	- Initialization: initialization process for all nodes
	- Security: ESP-NOW key management
	- Logging: system logs
	- Nodes: unified node management (status, MAC, firmware, etc.)
	- Manual: static HTML manual, ready for custom content<br/>
**Rationale:** Clear structure for users and developers, with reusable generic pages and customizable application-specific pages.<br/>
**Alternative considered:** Single-page design (too cluttered), or only application-specific pages (harder to find common features).

## Page Header

**REQ-HTMX-110:** The header of each page shall show the name of the project, the version number, and for non Home pages,a Home button and a sub title. For multi level pages, a Back button shall be shown in the header to go back to the previous page. The header is consistent across all pages.<br/>
**Rationale:** A consistent header provides a clear structure and navigation for users across all pages. The Home button allows users to easily return to the main page, while the Back button provides a way to navigate back through multi-level pages without losing context.<br/>
**Alternative considered:** No header or inconsistent headers across pages — rejected, would lead to a confusing

# Configuration

## Load Save Button

**REQ-HTMX-300:** The configuration page has a Load and Save button. Each changed setting is send to the webserver and takes in effect immediately. When the Load button is used, the website settings are overwritten. When the Save button is pressed, all settings are stored in NVS. For a successful Load or Save, the button changes temporarily in Loaded! or Saved!. In case of an error, the button changes to Error! temporarily. In case of a specific setting cannot be changed, the label of the setting will be temporarily changed into Error!.<br/>
**Rationale:** Provides a clear and immediate feedback to the user about the success or failure of their actions, improving the user experience and making it easier to understand the state of the system. Immediate effect of changes allows for quick testing and iteration without needing to reload the page or restart the system.<br/>
**Alternative considered:** No feedback on Load/Save actions — rejected, would leave users uncertain about whether their actions were successful. Changes only take effect after a page reload or system restart — rejected, would slow down the configuration process and make it less user-friendly.

## Category Panes

**REQ-HTMX-310:** The configuration page shall have its configurations in different panes, named according to the category of the settings. Each pane can be expanded or collapsed to show or hide the settings within it.<br/>
**Rationale:** Organizing settings into categorized panes improves the user experience by reducing clutter and making it easier for users to find and focus on specific settings. The ability to expand or collapse panes allows users to customize their view and focus on the settings that are relevant to them at any given time.<br/>
**Alternative considered:** All settings shown in a single list without categorization or collapsible panes — rejected, would be overwhelming and make it difficult for users to find specific settings, especially as the number of settings grows.

# Nodes

## Node properties

**REQ-HTMX-400:** The Nodes page provides unified management for all nodes (master and slaves), including:

	- Node number and name
	- Role (Master, Remote, Slave type)
	- Slave sequence number (for slaves)
	- Status (OK/NOK)
	- Last communication time
	- Uptime
	- Firmware version
	- Per-node firmware update button (chunked upload, live progress, retries, no checksum)
	- Configuration version
	- MAC address (editable, with Save button)
	- IP address (for webserver slaves/remotes)
**Rationale:** Comprehensive, actionable node management and monitoring in one place.<br/>
**Alternative considered:** Minimal or split node management/status (less user-friendly, harder to maintain).

## Firmware Update

**REQ-HTMX-410:** Firmware upload uses chunked POSTs (4KB), with frontend retry logic and a live progress line. Also, a checksum is used; TCP ensures integrity. During upload, SSE status updates are buffered to prevent UI glitches.<br/>
**Rationale:** Chunked uploads with retries improve reliability, especially on unstable connections. Live progress provides user feedback. Buffering SSE updates prevents UI issues during upload.<br/>
**Alternative considered:** Single POST upload (less reliable), no progress feedback (poorer UX), or allowing SSE updates during upload (UI glitches).

# Security 

# Security Page

**REQ-HTMX-500:** The security page shall show the current ESP-NOW security key and allow users to change it. When the key is changed, it is sent to the master to be spread to all slaves.<br/>
**Rationale:** The security page provides users with visibility into the current security settings of the system and allows them to easily update the ESP-NOW security key without needing to modify firmware. Sending the new key to the master for distribution ensures that all nodes in the system are updated with the new key, maintaining secure communication across the network.<br/>
**Alternative considered:** No security page or a security page without the ability to change the ESP-NOW key — rejected, would limit users' ability to manage their security settings and require firmware changes to update the key, which is less user-friendly and reduces security if the firmware is shared.

# Logging 

## Logging Page

**REQ-HTMX-600:** The logging page shall show the logs of the system, including messages sent and received, errors, and other relevant events. Logs can be filtered by node, role, or message type.<br/>
**Rationale:** The logging page provides users with valuable insights into the operation of the system, allowing them to monitor communication, identify errors, and understand the behavior of the system. The ability to filter logs by node, role, or message type helps users quickly find relevant information and troubleshoot issues more effectively.<br/>
**Alternative considered:** No logging page or a logging page without filtering options — rejected, would make it harder for users to monitor the system and identify issues, leading to a poorer user experience and more difficult troubleshooting.

# Manual 

## Static HTML Manual

**REQ-HTMX-420:** The Manual page is a static HTML page, ready for custom user manual/help content. No Back button or placeholder text is shown by default.<br/>
**Rationale:** Allows for project-specific documentation in a consistent, styled format.<br/>
**Alternative considered:** Markdown or dynamic/manual content (less control over layout/styling).
# Development and Testing

# ERROR HANDLING

## Failing GET/POST Actions

**REQ-HTMX-700:** When GET/POST messages do not succeed, an error is shown (briefly). For buttons the text will briefly turn red with 'Error' text.<br/>
**Rationale:** Provides immediate feedback to the user about the failure of their action, allowing them to understand that something went wrong and take corrective action if needed. This improves the user experience and helps prevent confusion or frustration when actions do not succeed.<br/>
**Alternative considered:** No error feedback on failed actions — rejected, would leave users uncertain about whether their actions were successful and could lead to confusion or frustration when things do not work as expected.

# Software Organization

# Testing

## Webserver Local Testing

**REQ-HTMX-430:** The webserver and website are developed and tested locally using a Python/Flask mock server, with all ESP32-specific calls mocked. The final target is an ESP32 webserver (ESP-IDF), serving the same static files and API contract.<br/>
**Rationale:** Enables rapid development, debugging, and UI testing before deploying to hardware.<br/>
**Alternative considered:** Direct-to-ESP32 development (slower, harder to debug).

# Hardware
