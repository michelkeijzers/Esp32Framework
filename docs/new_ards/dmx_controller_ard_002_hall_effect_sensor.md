# ADR-010: A1324 Hall Effect Sensor for Foot Pedal Position

## Status
Accepted

## Date
2026-03-17

## Authors
- Project Hardware Lead

## Context
FCB1010 foot pedal requires continuous position measurement for expression control. The decision was the sensing technology to use.

## Requirements Addressed
- DMX-REQ-040: System shall support continuous pedal position input

## Decision Drivers
- Foot pedals have high cycle count and wear is critical concern
- Magnetic sensing enables contactless measurement
- 16-bit resolution needed for smooth expression control
- A1324 is common in professional pedals for this application

## Options Considered

### Option A: A1324 Linear Hall Effect Sensor + ADS1115 ADC (Selected)
Use Hall effect sensor for contactless measurement with 16-bit ADC.
- ✅ Pro: Wear-free operation (no mechanical contact)
- ✅ Pro: Suitable for high-cycle footswitch (100,000+ cycles)
- ✅ Pro: 16-bit resolution enables smooth expression curves
- ✅ Pro: Proven in professional audio equipment
- ✅ Pro: ADS1115 provides I2C interface (no additional GPIO)
- ❌ Con: Higher cost than potentiometer (~5 USD vs 0.50 USD)
- ❌ Con: Requires magnet installation

### Option B: Potentiometer
Traditional variable resistor for position measurement.
- ✅ Pro: Cheap (~0.50 USD)
- ✅ Pro: Simple analog input (one ADC pin)
- ❌ Con: Mechanical contact wear (1,000-10,000 cycles typical)
- ❌ Con: Unacceptable for professional foot pedal use
- ❌ Con: Noise and non-linearity over lifetime

### Option C: Encoder
Rotary encoder for discrete position steps.
- ✅ Pro: Very durable
- ❌ Con: Discrete steps not suitable for smooth expression control
- ❌ Con: More expensive than potentiometer

## Decision
Adopt Option A: A1324 Hall Effect Sensor + ADS1115 ADC.

## Consequences
- Foot pedal remains wear-free and durable (100,000+ cycles expected)
- 16-bit resolution enables smooth, professional expression control
- Magnet integrated into pedal mechanism (non-invasive)
- ADS1115 ADC provides I2C interface (uses shared I2C bus)
- Minor cost increase but justified by durability and performance
- Long-term reliability suitable for professional use
