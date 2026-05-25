# Smart Gate Controller

An ESP32-based automated gate system that uses an ultrasonic sensor to detect vehicles and control a servo motor gate. Built across three parts: embedded hardware simulation, a visual programming block, and a live web dashboard.

---

## Part 1 — ESP32 Gate Controller (Wokwi)

### Overview
An embedded system simulated in [Wokwi](https://wokwi.com) using an ESP32, an HC-SR04 ultrasonic sensor, a servo motor, and an LED. The system continuously measures the distance in front of the gate. If a vehicle is detected within the threshold distance, the gate closes. When the vehicle leaves, a 5-second countdown begins — if no vehicle is detected during that window, the gate opens. An LED blinks whenever the gate is in motion.

### How to Run
1. Go to [wokwi.com](https://wokwi.com) and create a new ESP32 project
2. Replace the default `sketch.ino` with the one in this folder
3. Replace `diagram.json` with the one in this folder
4. Add `ESP32Servo` to `libraries.txt`
5. Press the play button to start the simulation

<img width="841" height="613" alt="Image" src="https://github.com/user-attachments/assets/62f6102e-6603-4889-a595-08772ddfebaa" />

---

## Part 2 — Custom Blockly Block

### Overview
A custom [Blockly](https://developers.google.com/blockly) block called `open_gate_with_speed` that accepts a speed input from 1 to 10. When connected to a number block and the "Generate Code" button is pressed, it produces JavaScript code that sweeps a servo motor from 0° to 90° at the specified speed — simulating a gate opening.

### How It Works
- Speed input is clamped between 1 and 10
- Step delay is calculated as `55 - speed × 5` milliseconds per degree
  - Speed 1 → 50 ms/° (slow, ~4.5 seconds for full sweep)
  - Speed 10 → 5 ms/° (fast, ~0.45 seconds for full sweep)
- The generated code uses a `for` loop calling `servo.write(angle)` at each degree step

### Example Output (speed = 7)
```js
(function() {
  var speed = Math.min(10, Math.max(1, 7));
  var stepDelay = Math.round(55 - 7 * 5); // 20ms per degree
  for (var angle = 0; angle <= 90; angle++) {
    servo.write(angle);
    delay(stepDelay);
  }
})();
```

### Files
- `index.html` — Blockly workspace UI
- `open_gate_with_speed.js` — custom block definition and code generator
- `main.js` — workspace initialisation

### How to Run
1. Open `index.html` directly in any browser (no server needed)
2. Drag the **"open gate at speed"** block from the toolbox onto the canvas
3. Plug a **Number** block into the speed socket and enter a value (1–10)
4. Click **Generate Code** — the output appears in the box below

> 📷 **Screenshot to add:** The Blockly editor with the custom block connected to a number (e.g. 7), and the generated servo code visible in the output box below.

---

## Part 3 — Site Management Dashboard

### Overview
A browser-based dashboard that simulates the gate controller in real time. The "Live Feed" panel shows the current gate state with an animated barrier gate visual. A draggable sensor slider lets the user manually control the simulated distance reading — the gate responds exactly as the real ESP32 system would.

### Features
- **Live Feed** — animated barrier gate that opens and closes with a smooth sweep transition
- **Sensor Reading** — draggable slider (1–400 cm) with a colour-coded distance bar; turns red when a vehicle is within 100 cm
- **Gate State Panel** — shows current position, servo angle, last trigger time, and total event count
- **Event Log** — timestamped log of every state change
- **Simulation Uptime** — live counter showing how long the current session has been running

### Simulation Flow
1. Press **Start Simulation** — gate starts open, slider enables
2. Drag slider left to ≤ 100 cm → vehicle detected, gate closes
3. Drag slider right above 100 cm → 5-second countdown begins, then gate opens
4. Press **Stop Simulation** to freeze everything

### Files
- `dashboard.html` — single self-contained file with all HTML, CSS, and JavaScript inline. Open directly in any browser, no server or dependencies required.

> 📷 **Screenshot to add 1:** Dashboard with the gate open (slider at high distance, green "Gate Open" badge visible).
> 
> 📷 **Screenshot to add 2:** Dashboard with the gate closed (slider dragged to low distance, red vehicle detected indicator, "Gate Closed" badge).

---

## Project Structure

```
smart-gate-controller/
├── part1-wokwi/
│   ├── sketch.ino
│   └── diagram.json
├── part2-blockly/
│   ├── index.html
│   ├── open_gate_with_speed.js
│   └── main.js
├── part3-dashboard/
│   └── dashboard.html
└── README.md
```
