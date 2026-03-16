# DMX Webserver Development Setup

## Overview
To develop and test the DMX webserver project locally, you need to run both the frontend (Vite) and backend (Python Flask) servers. This enables static website files and dynamic API endpoints for full functionality.

---

## 1. Frontend: Vite Dev Server
- **Command:** `npm run dev`
- **Location:** `website/dmx_project`
- **Purpose:** Serves static website files, enables hot-reloading for frontend development.
- **URL:** [http://localhost:5173](http://localhost:5173) (or next available port)

---

## 2. Backend: Python Flask Server
- **Command:** `python server.py`
- **Location:** `website/dmx_project`
- **Purpose:** Serves API endpoints for dynamic content (presets, control, nodes, etc.)
- **URL:** [http://localhost:8080](http://localhost:8080)

---

## 3. How They Work Together
- The frontend makes AJAX/API calls to the backend Flask server.
- If only one server is running, dynamic features (like preset lists) will not work.
- **Both must be running** for full functionality.

---

## 4. Typical Workflow
1. Open two terminals:
    - Terminal 1: `cd website/dmx_project && npm run dev`
    - Terminal 2: `cd website/dmx_project && python server.py`
2. Open [http://localhost:5173](http://localhost:5173) in your browser.
3. Interact with the web UI. Dynamic content is fetched from the Flask backend.

---

## 5. Troubleshooting
- If preset lists or control pages are empty, check that `server.py` is running.
- If you see port conflicts, Vite will automatically use the next available port.
- For production, build the site with `npm run build` and deploy the backend as needed.

---

## Summary Table
| Service   | Command            | URL                   | Purpose                |
|-----------|--------------------|-----------------------|------------------------|
| Frontend  | npm run dev        | http://localhost:5173 | Static website, dev UI |
| Backend   | python server.py   | http://localhost:8080 | API endpoints, dynamic |

---

For more details, see project README or ask for help.
