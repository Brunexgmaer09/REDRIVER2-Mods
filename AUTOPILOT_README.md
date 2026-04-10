# Sistema de AutoPilot - REDRIVER2

## O que e

Sistema que permite ao jogador ativar piloto automatico no carro, usando a mesma IA dos carros civis do jogo (CivControl). O carro passa a dirigir sozinho pelas ruas, respeitando semaforos, mudando de faixa, etc.

## Como usar

1. Entre num carro no jogo
2. Aperte **G** no teclado para ativar o autopilot
3. Aperte **G** novamente para desativar
4. Voce pode sair do carro normalmente durante o autopilot (Up+Triangle ou R3)

## Arquivos modificados

### src_rebuild/Game/C/main.h
- Declaracao das funcoes e variavel global `gAutoPilot`
- `AlternarAutoPilot()` - toggle on/off
- `DesativarAutoPilot()` - desativa o autopilot

### src_rebuild/Game/C/main.c
**Variaveis globais adicionadas (linha ~121):**
- `int gAutoPilot` - flag indicando se autopilot esta ativo
- `static CIV_STATE gAutoPilotState` - estado da IA civil salvo entre frames
- `static char* gAutoPilotPadId` - padid do player salvo antes de ativar

**Funcoes adicionadas (antes de State_GameLoop):**
- `DesativarAutoPilot()` - restaura controlType e padid, zera flag
- `AlternarAutoPilot()` - quando ativa: salva padid, chama InitCivState() pra encontrar a estrada e inicializar pathfinding da IA, salva CIV_STATE no buffer global, restaura player. Quando desativa: chama DesativarAutoPilot()

**Game loop modificado (case CONTROL_TYPE_PLAYER):**
- Quando `gAutoPilot` ativo e o carro e do player:
  - Se apertar botao de sair do carro: desativa autopilot e processa saida normal
  - Senao: salva padid, troca temporariamente pra CIV_STATE e hndType=1, chama CivControl(), salva estado de volta, restaura padid e hndType=0
- Quando autopilot inativo: fluxo normal sem alteracao

**InitGameVariables (reset):**
- `gAutoPilot = 0` e `gAutoPilotPadId = NULL` no reset do jogo

### src_rebuild/Game/C/players.c
- Adicionado `#include "main.h"`
- `ChangeCarPlayerToPed()` chama `DesativarAutoPilot()` quando player sai do carro

### src_rebuild/Game/C/pedest.c
- Adicionado `#include "main.h"`
- `SetupCivJump()` - nao gera felony por "assustar pedestres" durante autopilot
- `set_coll_box()` - trata carro do player como carro civil durante autopilot (caixa de colisao menor, pedestres nao fogem)

### src_rebuild/Game/C/felony.c
- Adicionado `#include "main.h"`
- `CheckPlayerMiscFelonies()` - pula toda checagem de felony durante autopilot (derrapagem, velocidade, mao errada, etc)

### src_rebuild/redriver2_psxpc.cpp
- `AutoPilotKeyHandler()` - captura tecla G via SDL_SCANCODE_G, chama AlternarAutoPilot()
- `GameReleaseKeys()` - handler combinado pra release (freecamera + autopilot)
- `GameDebugKeys()` - adicionada chamada ao AutoPilotKeyHandler
- Registro do handler: sempre ativo tanto em debug quanto release

### src_rebuild/Game/C/targets.c
- Correcao pre-existente: cast `(int*)pOut` na chamada RotTransPers (compatibilidade com compilador novo)

## Como funciona internamente

O `CAR_DATA` usa uma **union** pro campo `ai`:
- Quando CONTROL_TYPE_PLAYER: `ai.padid` (ponteiro pro pad do jogador)
- Quando CONTROL_TYPE_CIV_AI: `ai.c` (struct CIV_STATE com dados de pathfinding)

A cada frame no autopilot:
1. Salva o `padid` do player
2. Troca `controlType` pra CIV_AI e `hndType` pra 1 (freio suave)
3. Carrega o `CIV_STATE` salvo na union
4. Chama `CivControl(cp)` - mesma funcao dos carros civis
5. Salva o `CIV_STATE` de volta pro buffer global
6. Restaura `controlType` pra PLAYER, `hndType` pra 0 e `padid`

O `CivControl` internamente:
- `CivSteerAngle()` - calcula angulo de direcao baseado nos nodes da estrada
- `CivAccel()` - calcula aceleracao/frenagem respeitando semaforos e outros carros
- Muda de faixa, respeita limites de velocidade, para em semaforos vermelhos

## Como compilar

1. `windows_dev_prepare.ps1` (baixa dependencias + premake5)
2. Baixar PsyCross manualmente (submodulo git) pra `src_rebuild/PsyCross/`
3. Abrir `src_rebuild/project_vs2019_windows/REDRIVER2.sln` no Visual Studio
4. Redirecionar projetos pro toolset atual se necessario
5. Configuracao: **Release_dev** | Plataforma: **Win32**
6. Build > Recompilar Solucao
7. Copiar exe + SDL2.dll + OpenAL32.dll pra pasta `data/`
8. Configurar `config.ini` com caminho do BIN do Driver 2

## Ideias futuras

- [ ] Zerar felony ao entrar em carro de policia estacionado (nao ser perseguido)
- [ ] Mostrar indicador visual na tela quando autopilot esta ativo (HUD)
- [ ] Permitir definir destino/rota pro autopilot
- [ ] Velocidade customizavel (lento/normal/rapido)
