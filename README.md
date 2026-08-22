## Linux (Ubuntu/Debian)

### system Dependencies (needed by Raylib)
```bash
sudo apt-update
sudo apt install libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libgl-dev libgl1-mesa-dev
```
## Mancata visualizzazione in WSL post upgrade ubuntu: (da power shell admin)
```bash
wsl --system sh -lc "pkill -9 weston"
```

![Testo alternativo](assets/cppang.gif)