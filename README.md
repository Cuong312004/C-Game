# 🎮 2‑D Action Adventure – C++ / SDL

A fast‑paced platformer where you guide a ninja through trap‑filled stages and duel a gigantic boss.  
Written in modern C++ (C++17) with **SDL 2** for rendering, sound, and input.

![Game_play_1](https://github.com/Cuong312004/C-Game/blob/main/Screenshot%202025-07-05%20224129.png)
![Game_play_2](https://github.com/Cuong312004/C-Game/blob/main/Screenshot%202025-07-05%20224203.png)
![Game_play_3](https://github.com/Cuong312004/C-Game/blob/main/Screenshot%202025-07-05%20224338.png)
---

## ✨ Gameplay at a glance
| Feature | Notes |
|---------|-------|
| **Platforming** | Run, jump, wall‑slide & double‑jump  
| **Combat**      | Throw **kunai** or slash at close range  
| **Boss battle** | Multi‑phase boss with separate HP bar & explosion animation  
| **Tile‑map engine** | JSON tile‑maps, camera follow, parallax BG  
| **OOP design**  | `GameObject`, `Player`, `Boss`, `Kunai`, `Map`,…  
| **Modular states** | Intro → Menu → Play → Game Over via `GameStateBase`  
| **Assets** | Sprite‑sheet animations, SFX, music – easy to swap  

---

## 🚀 Build & run

### Windows + Visual Studio 2019 / 2022
1. Install **SDL 2.28+ development** package.  
2. Add SDL *include* and *lib* folders to the project (or set `SDL2_DIR` env‑var).  
3. Open `GAME.sln` → **Build → Run**.

---

## 🎮 Controls (default)

| Action          | Key / Button |
|-----------------|--------------|
| Move            | ←  →  /  **A D** |
| Jump / double   | **Space**    |
| Throw Kunai     | **J**        |
| Slash / melee   | **K**        |
| Pause           | **Esc**      |


---

## 🧩 Extending the game
* **Add levels** → export new TMX/JSON maps into `res/maps/`.
* **New enemies** → inherit from `GameCharacter`, implement `Update()` & `Render()`.
* **UI / HUD** → modify `GameStatePlay::DrawHUD()`.
* **Mobile / gamepad** → replace `InputManager` with SDL GameController API.

---

## ▶️ Demo video 
* Demo: <https://youtu.be/your_demo_link>  

---

Happy hacking! ✌️
