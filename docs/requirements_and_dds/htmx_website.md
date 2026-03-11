# HTMX WEBSITE REQUIREMENTS

# Pages

**REQ-HTTP-100:** The webserver will be divided in pages.
**Rationale:** The structure needs to be clear for users.
**Alternative considered:** Everything in one page.

**REQ-HTTP-110:** Every website has a Status, Initialization, Security, Logging, Firmware and Manual page.
**Rationale:** These pages are not application specific.
**Alternative considered:** -

**REQ-HTTP:120:** The configuration page has a Load and Save button. Each changed setting is send to the webserver and takes in effect immediately. When the Load button is used, the website settings are overwritten. When the Save button is pressed, all settings are stored in NVS. For a successful Load or Save, the button changes temporarily in Loaded! or Saved!. In case of an error, the button changes to Error! temporarily. In case of a specific setting cannot be changed, the label of the setting will be temporarily changed into Error!.
**Rationale:** Let the user now of a successfull or unsuccessfull procedure.
**Alternative considered:** A longer error text.

# Firmware

**REQ-HTTP-500:** Firmware version of all slaves shall be visible in the Htmx UI.<br/>
**Rationale:** Firmware versions need to be visible for debugging, monitoring, and ensuring compatibility across the system.<br/>
**Alternative considered:** No firmware version visibility — rejected, would make debugging and monitoring more difficult.

# ERROR HANDLING

**REQ-HTTP-700:** When GET/POST messages do not succeed, an error is shown (briefly).
**Rationale:** Ensures the user is aware of an error.
**Alternative considered:** No error is shown, but then the user is unaware.


# Software Organization

# Testing

# Hardware
