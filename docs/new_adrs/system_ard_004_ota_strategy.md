# ADR-007: Three-Tier OTA Strategy for Flexibility

## Status
Accepted

## Date
2026-03-17

## Authors
- Lead Firmware Architect

## Context
Nodes are installed in physical enclosures without easy USB access. Firmware updates must be wireless. The decision was what OTA strategies to support.

## Requirements Addressed
- SYS-REQ-042: Three OTA approaches shall be supported

## Decision Drivers
- USB access impractical after installation in enclosures
- Not all nodes have Wi-Fi capability or antenna
- Different scenarios require different approaches
- Flexibility needed for different deployment scenarios
- Approach 3 deferred due to development effort

## Options Considered

### Option A: Webserver via Wi-Fi (Tier 1)
Standard ESP-IDF OTA: webserver node receives firmware via Wi-Fi and updates itself.
- ✅ Pro: Simple, native ESP-IDF support
- ✅ Pro: Already implemented in base design
- ✅ Pro: Works immediately for webserver node
- ❌ Con: Only works for webserver which has Wi-Fi

### Option B: Nodes via Temporary Wi-Fi (Tier 2)
Node temporarily enables Wi-Fi STA mode, connects to router, downloads firmware OTA, reboots back to ESP-NOW only.
- ✅ Pro: Works for devices close to router with Wi-Fi antenna
- ✅ Pro: Works in plastic enclosures with external antenna access
- ✅ Pro: Node retains autonomy
- ❌ Con: Requires Wi-Fi antenna on node
- ❌ Con: Only works if node is close enough to router

### Option C: OTA Proxy via ESP-NOW (Tier 3) - Deferred
Webserver downloads firmware via Wi-Fi, forwards to node via ESP-NOW in chunks (~2500 chunks at 200 bytes).
- ✅ Pro: Works for all nodes regardless of antenna or enclosure
- ✅ Pro: Master can supervise transfer
- ✅ Pro: No Wi-Fi needed on node
- ❌ Con: Significant development effort
- ❌ Con: Many small transfer requests to webserver
- ❌ Con: Deferred for future implementation

## Decision
Adopt Option A + B as immediately available, with Option C deferred.

## Consequences
- Webserver supports OTA via Wi-Fi immediately.
- Nodes with Wi-Fi can perform temporary Wi-Fi OTA.
- Nodes without Wi-Fi await implementation of ESP-NOW proxy approach (Tier 3).
- Long-term goal is to support all scenarios via Tier 3.
- Two-tier approach satisfies most immediate deployment needs.
