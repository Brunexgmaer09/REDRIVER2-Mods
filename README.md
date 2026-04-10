# REDRIVER2-Mods (Reverse-Engineered Driver 2 - Custom Mods)

> Fork de [OpenDriver2/REDRIVER2](https://github.com/OpenDriver2/REDRIVER2) com mods customizados de gameplay.

---

## Mods Adicionados

### Modo Cop (tecla J)
Permite ao player controlar o carro de policia com IA autonoma.

- **Ativacao**: pressione `J` enquanto estiver em um carro de policia (modelo 3)
- **Modo Patrulha** (`gModoCop = 1`): o carro segue as ruas automaticamente via `CivControl`, respeitando semaforos e faixas
- **Modo Perseguicao** (`gModoCop = 2`): ativado automaticamente quando uma perseguicao civil comeca — o carro do player usa `CopControl` (PURSUER_AI) para perseguir o alvo pelas ruas
- **Sirene automatica**: som e luz piscante da sirene ativados automaticamente no modo perseguicao
- **Imortalidade durante chase**: dano do carro zerado a cada frame durante a perseguicao
- **Desativacao**: pressione `J` novamente ou o botao de sair do carro

---

### Sistema de Perseguicao Civil (`AtualizarPerseguicaoCivil`)
Perseguicoes autonomas de carros civis pelas ruas, independente do player.

- Um carro civil aleatorio e selecionado como fugitivo (`gFugitivo`) a cada intervalo
- Ate **60 carros de policia** proximos sao convertidos automaticamente em PURSUER_AI para perseguir o alvo
- Carros de policia patrulhando (`CONTROL_FLAG_COP`) tambem entram na perseguicao automaticamente
- Se um civil bater no carro do player em modo Cop, ele vira o novo fugitivo (`gInfrator`)
- **Duracao maxima**: 60 segundos — apos isso o fugitivo some do mapa
- **Respawn de cops distantes**: a cada 1 segundo, cops a mais de 33000 unidades do alvo sao removidos e substituidos por novos mais proximos
- **Configuracoes de dificuldade**: durante a perseguicao, cops ficam mais rapidos e agressivos (`gCopDifficultyLevel = 2`, `gCopDesiredSpeedScale = 6144`, imortalidade ativada)

---

### Auto Piloto
Controle autonomo do carro do player pelas ruas via `CivControl`.

- Ativado por tecla dedicada
- Suporta comandos de direcao manual (esquerda/direita) para influenciar o trajeto nas esquinas

---

### Melhorias de IA
- Cops com alvo (`alvo`) usam calculo de velocidade otimizado baseado em `gCopDesiredSpeedScale`
- Cops distantes do alvo sao respawnados proximos para manter a pressao na perseguicao
- Tratamento correto do estado CIV/COP na transicao entre modos (sem corrupcao de memoria)

---

Game running on Windows:

![](https://i.ibb.co/2q1pp06/red2.png)

Game running in Firefox Web Browser:

![](https://i.ibb.co/JxfC5xX/aaa.png)

Game running on Playstation (emulated)

![](https://i.ibb.co/ydLsK9z/aaa.png)

Build status (Windows and Linux):
[![Build status](https://ci.appveyor.com/api/projects/status/9abepvls6jexapqy/branch/master?svg=true)](https://ci.appveyor.com/project/SoapyMan/redriver2-10jm8/branch/master)

### Information
- This is an original game - it was carefully and completely disassembled and translated from MIPS back to C (except Memory Card menu) - ***no emulation involved***
- Game has been *significantly improved over the original Playstation version*, original bugs were fixed and completed some unfinished gameplay aspects
- It now runs on Windows, Linux and soon to be on the other platforms (including backport to Playstation) and utilizes [Psy-X (Psy-Cross) (formely extended TOMB5 emulator)](https://github.com/OpenDriver2/REDRIVER2/tree/master/src_rebuild/PsyX) as a layer for porting from Playstation
- Basic modding support - with textures and models replacement provided with [OpenDriver2Tools](https://github.com/OpenDriver2/OpenDriver2Tools)

### How is it done?
- All information (variables, types and function names) have been obtained from debugging symbols (.SYM), driver_psx_level and DLE
- Ghidra project (based on Italian SYM) to deal with overlays, simple code complex branching - semi-auto decompilation
- IDB based on Spanish SYM when dealing with things Ghidra can't handle properly - manual decompilation (mostly GTE code)

History:
- Feb 19, 2019 - created skeleton, one year long preparations
- Mar 28, 2020 - started work on reimplementing the game, game intro running
- Sep 19, 2020 - reimplementing game complete - game is fully playable
- Jan 15, 2021 - refactoring complete

### How to use
See [Wiki/Installation Instructions](https://github.com/OpenDriver2/REDRIVER2/wiki/Installation-instructions)

### How can I contribute?
See [Contributing to project](https://github.com/OpenDriver2/REDRIVER2/wiki/Contributing-to-project) page

### What's next
- ***OpenDriver2*** project - complete rewrite with lots of new features such as *new renderer and sound engine, Lua scripting, Driver 1 content support*

### Credits
- **SoapyMan** - lead reverse engineer and programmer
- **Fireboyd78** - code refactoring and improvements
- **Krishty, someone972** - early formats decoding
- **Gh0stBlade** - HLE Emulator code used as a base for Psy-Cross [(link)](https://github.com/TOMB5/TOMB5/tree/master/EMULATOR)
- **Ben Lincoln** - [This Dust Remembers What It Once Was](https://www.beneaththewaves.net/Software/This_Dust_Remembers_What_It_Once_Was.html) (*TDR*)
- **Stohrendorf** - [Symdump](https://github.com/stohrendorf/symdump) utility
