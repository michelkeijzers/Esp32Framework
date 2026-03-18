# ADR-002: Common Master and Remote Code Across Projects

## Status
Accepted

## Date
2026-03-17

## Authors
- Lead Firmware Architect

## Context
Master and Remote roles are deployed across multiple projects. The decision was whether their code should be project-specific or fully common.

## Requirements Addressed
- SYS-REQ-003: Master and remote code shall be fully common between projects

## Decision Drivers
- Master is a blind message router with no project knowledge
- Remote is a simple heartbeat sender with minimal logic
- Code reuse across projects reduces maintenance burden
- Avoiding firmware fragmentation simplifies deployments

## Options Considered

### Option A: Fully Common Code
Master and remote code is identical across all projects, never reflashed between projects.
- ✅ Pro: Maximum code reuse
- ✅ Pro: Simpler maintenance and fewer bugs
- ✅ Pro: Single firmware for all installations
- ✅ Pro: No project-specific logic leakage into master
- ❌ Con: Less flexibility for project-specific requirements

### Option B: Per-Project Code
Each project has its own master and remote code.
- ✅ Pro: Maximum flexibility for project-specific needs
- ❌ Con: Code fragmentation and duplication
- ❌ Con: Higher maintenance burden
- ❌ Con: Increased risk of bugs and divergence

## Decision
Adopt Option A: Fully Common Code for Master and Remote.

## Consequences
- Master and remote roles are compiled once and used in all projects.
- Any project-specific logic stays in other roles (Webserver, Node).
- Master and remote receive no firmware updates between projects.
- Changes to master/remote logic require careful review for cross-project compatibility.
