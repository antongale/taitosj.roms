;========================================================================
;  Taito System SJ - Hardware Register Definitions
;  Shared include for all .asm files in this folder
;
;  Source: Taito System SJ Hardware Reference Manual v0.1
;  Naming follows the manual where it provides a name.
;
;  Usage:    INCLUDE "taisj_hw.inc"
;  Guarded with IFNDEF so it can be included safely from multiple files.
;========================================================================

        IFNDEF  TAISJ_HW_INC
        DEFINE  TAISJ_HW_INC

;------------------------------------------------------------------------
; Z80 main CPU memory map
;------------------------------------------------------------------------

; Program ROM
ROM_BASE        EQU $0000       ; $0000-$5FFF program ROM (fixed)
ROM_BANKED      EQU $6000       ; $6000-$7FFF banked ROM (selected by COIN_SET bit 7)
ROM10           EQU $E000       ; $E000-$FFFF expansion ROM socket (unpopulated on most boards)

; Work RAM
WORK_RAM        EQU $8000       ; $8000-$87FF (2KB)
STACK_TOP       EQU $87FE

; MCU communication ($8800-$8FFF, only on boards with MC68705)
MCU_DATA        EQU $8800       ; data exchange latch (R/W)
MCU_HSHK        EQU $8801       ; handshake / IRQ control (R/W)

; VRAM bitplanes - bank 0 (tiles 0-255), write-only
VRAM_BP0_B0     EQU $9000       ; bitplane 0
VRAM_BP1_B0     EQU $9800       ; bitplane 1
VRAM_BP2_B0     EQU $A000       ; bitplane 2

; VRAM bitplanes - bank 1 (tiles 256-511), write-only
VRAM_BP0_B1     EQU $A800
VRAM_BP1_B1     EQU $B000
VRAM_BP2_B1     EQU $B800

; General-purpose R/W RAM (also used for sprite collision data on some games)
GP_RAM          EQU $C000       ; $C000-$C3FF (1KB)

; Tilemap RAM (each layer 32x32 tiles, 1KB)
TILEMAP1        EQU $C400       ; layer 1
TILEMAP2        EQU $C800       ; layer 2
TILEMAP3        EQU $CC00       ; layer 3

; First visible tilemap row (rows 0-1 / first 64 bytes are above visible area)
TILEMAP1_VIS    EQU $C440       ; first visible row of layer 1
TILEMAP2_VIS    EQU $C840       ; first visible row of layer 2
TILEMAP3_VIS    EQU $CC40       ; first visible row of layer 3

; Per-column vertical scroll (SCRRQ), 32 bytes per layer
COLSCROLL_L1    EQU $D000       ; layer 1 column scroll
COLSCROLL_L2    EQU $D020       ; layer 2 column scroll
COLSCROLL_L3    EQU $D040       ; layer 3 column scroll

; Sprite RAM (64 entries x 4 bytes; only 24 visible per active bank)
SPRITE_RAM      EQU $D100

; Palette RAM (64 entries x 2 bytes; 9-bit RGB stored across low/high bytes)
PAL_RAM         EQU $D200

; Layer priority register (5-bit selector into priority PROM)
PRIORITY        EQU $D300

;------------------------------------------------------------------------
; Hit bus read registers
;------------------------------------------------------------------------
H0X             EQU $D400       ; sprites 0-7  collision mask
H1X             EQU $D401       ; sprites 8-15 collision mask
H2X             EQU $D402       ; sprites 16-23 collision mask
HOBJ            EQU $D403       ; layer/sprite collision flags

; EXRHR - external ROM data read (auto-incrementing); $D404-$D407 mirror
EXRHR           EQU $D404

;------------------------------------------------------------------------
; Input registers (read-only, active-low)
;------------------------------------------------------------------------
IN0             EQU $D408       ; player 1 joystick + buttons
IN1             EQU $D409       ; player 2 joystick + buttons
DSA             EQU $D40A       ; DIP switch A
IN3             EQU $D40B       ; coin / start
IN4             EQU $D40C       ; secondary controls (gun direction etc.)
IN5             EQU $D40D       ; sound CPU status (bits 7:4)
;   DS.B = AY0 port A, DS.C = AY0 port B (read via AY0_ADDR / AY0_DATA)

;------------------------------------------------------------------------
; Main board AY-3-8910 #0
;------------------------------------------------------------------------
AY0_ADDR        EQU $D40E       ; write AY register number
AY0_DATA        EQU $D40F       ; write AY register value

;------------------------------------------------------------------------
; Tilemap scroll registers
;------------------------------------------------------------------------
SPH1            EQU $D500       ; layer 1 horizontal
SPV1            EQU $D501       ; layer 1 vertical
SPH2            EQU $D502       ; layer 2 horizontal
SPV2            EQU $D503       ; layer 2 vertical
SPH3            EQU $D504       ; layer 3 horizontal
SPV3            EQU $D505       ; layer 3 vertical

;------------------------------------------------------------------------
; Mode registers
;------------------------------------------------------------------------
SMD12           EQU $D506       ; tilemap 1+2 palette / VRAM bank
SMD3            EQU $D507       ; tilemap 3 palette / VRAM bank + sprite palette
HTCLR           EQU $D508       ; write any value to clear hit bus

;------------------------------------------------------------------------
; External ROM addressing (for EXRHR)
;------------------------------------------------------------------------
EXROM1          EQU $D509       ; ROM address low byte
EXROM2          EQU $D50A       ; ROM address high byte

;------------------------------------------------------------------------
; Sound board command channel
;------------------------------------------------------------------------
EPORT1          EQU $D50B       ; 8-bit command to sound CPU
EPORT2          EQU $D50C       ; single-bit signal (data bus bit 0)

;------------------------------------------------------------------------
; System control
;------------------------------------------------------------------------
TIME_RESET      EQU $D50D       ; watchdog (write any value once per frame)
COIN_SET        EQU $D50E       ; coin lock / sound stop / bank sel
EXPORT          EQU $D50F       ; output to priority PAL (Alpine Ski only)
SOFF            EQU $D600       ; sprite/layer enable + global flip

; Optional SCRAM RAM (Kick Start: Wheelie King only)
SCRAM           EQU $D800       ; $D800-$DFFF (2KB)

;------------------------------------------------------------------------
; SOFF register bits ($D600)
;------------------------------------------------------------------------
SOFF_HINV       EQU $01         ; bit 0 - global horizontal flip
SOFF_VINV       EQU $02         ; bit 1 - global vertical flip
SOFF_OBJEX      EQU $04         ; bit 2 - sprite RAM bank select (0=bank0, 1=bank1)
SOFF_SN1OFF     EQU $10         ; bit 4 - tilemap 1 enable (1=on)
SOFF_SN2OFF     EQU $20         ; bit 5 - tilemap 2 enable
SOFF_SN3OFF     EQU $40         ; bit 6 - tilemap 3 enable
SOFF_OBJOFF     EQU $80         ; bit 7 - sprite enable
SOFF_ALL_ON     EQU $F0         ; sprites + all 3 layers, no flip

;------------------------------------------------------------------------
; HOBJ collision bits ($D403)
;------------------------------------------------------------------------
HOBJ_OB1        EQU $01         ; sprite ∩ tilemap 1
HOBJ_OB2        EQU $02         ; sprite ∩ tilemap 2
HOBJ_OB3        EQU $04         ; sprite ∩ tilemap 3
HOBJ_S12        EQU $08         ; tilemap 1 ∩ tilemap 2
HOBJ_S13        EQU $10         ; tilemap 1 ∩ tilemap 3
HOBJ_S23        EQU $20         ; tilemap 2 ∩ tilemap 3

;------------------------------------------------------------------------
; IN0 / IN1 - player input bits (active-low)
;------------------------------------------------------------------------
IN_LEFT         EQU $01         ; bit 0
IN_RIGHT        EQU $02         ; bit 1
IN_DOWN         EQU $04         ; bit 2
IN_UP           EQU $08         ; bit 3
IN_BTN1         EQU $10         ; bit 4
IN_BTN2         EQU $20         ; bit 5

;------------------------------------------------------------------------
; IN3 - coin / start bits (active-low)
;------------------------------------------------------------------------
IN3_COIN2       EQU $10         ; bit 4
IN3_COIN1       EQU $20         ; bit 5
IN3_START1      EQU $40         ; bit 6
IN3_START2      EQU $80         ; bit 7

;------------------------------------------------------------------------
; IN4 - secondary controls (gun direction, service)
;------------------------------------------------------------------------
IN4_GUN_LEFT    EQU $01
IN4_GUN_RIGHT   EQU $02
IN4_GUN_DOWN    EQU $04
IN4_GUN_UP      EQU $08
IN4_SERVICE     EQU $10

;------------------------------------------------------------------------
; COIN_SET register bits ($D50E)
;------------------------------------------------------------------------
COIN_SET_LOCK   EQU $01         ; bit 0 - coin lockout
COIN_SET_MUTE   EQU $02         ; bit 1 - sound stop (mute)
COIN_SET_BANK   EQU $80         ; bit 7 - program ROM bank select

;------------------------------------------------------------------------
; SMD12 register bits ($D506) - tilemap 1+2 mode
;------------------------------------------------------------------------
SMD12_CCH1      EQU $08         ; bit 3 - tilemap 1 VRAM bank (0=bank0)
SMD12_CCH2      EQU $80         ; bit 7 - tilemap 2 VRAM bank
;   bits 2:0 = MD1 palette bank for tilemap 1
;   bits 6:4 = MD2 palette bank for tilemap 2

;------------------------------------------------------------------------
; SMD3 register bits ($D507) - tilemap 3 + sprite mode
;------------------------------------------------------------------------
SMD3_CCH3       EQU $08         ; bit 3 - tilemap 3 VRAM bank
;   bits 2:0 = MD3 palette bank for tilemap 3
;   bits 5:4 = MD0 sprite palette bank (combined with OMD attribute bit)

;------------------------------------------------------------------------
; Sprite attribute byte bits (sprite RAM offset +2)
;------------------------------------------------------------------------
SPR_HFLIP       EQU $01         ; bit 0 - horizontal flip (OBJ_CINV)
SPR_VFLIP       EQU $02         ; bit 1 - vertical flip
SPR_OMD         EQU $04         ; bit 2 - sprite colour bank (upper colour bit)

;------------------------------------------------------------------------
; Sprite RAM offsets (within each 4-byte entry)
;------------------------------------------------------------------------
SPR_OFF_X       EQU 0           ; X position (0=left)
SPR_OFF_Y       EQU 1           ; Y position (224=top, 0=bottom)
SPR_OFF_ATTR    EQU 2           ; attributes (HFLIP/VFLIP/OMD)
SPR_OFF_TILE    EQU 3           ; 7-bit tile code

;------------------------------------------------------------------------
; Hardware quirks (documented in manual)
;------------------------------------------------------------------------
; Horizontal scroll fine field has +5 phase offset:
;   fine = (pixel + 5) & 7
; Tile boundary is at fine 4->5, not the expected 7->0.
SPH_FINE_OFFSET EQU 5

; Sprite Y to tilemap row conversion (rows below TILEMAPx_VIS):
;   sprite_Y = 224 - (row * 8)
SPR_Y_TOP       EQU 224         ; sprite Y that places sprite top at top of screen


;========================================================================
; Sound board hardware (Z80 #2 address space)
;
;   These addresses are valid only from code running on the sound CPU
;   (taisj_sound.asm). They will conflict with main-CPU addresses if
;   accidentally used from main-CPU code, so they are grouped at the end.
;========================================================================

; Sound board ROM
SND_ROM_BASE    EQU $0000       ; $0000-$3FFF (4 x 4KB ROMs)

; Sound board RAM
SND_RAM         EQU $4000       ; $4000-$43FF (1KB)

; Sound board AY-3-8910 chips (each: even=addr, odd=data)
AY1_BASE        EQU $4800       ; AY-3-8910 #1
AY2_BASE        EQU $4802       ; AY-3-8910 #2
AY3_BASE        EQU $4804       ; AY-3-8910 #3

; Sound board command interface
CMD_LATCH       EQU $5000       ; EPORT1 read (clears DB3 pending flag)
STATUS_REG      EQU $5001       ; bit 3 = DB3 pending, bit 2 = DB2 (EPORT2)

; Sound board STATUS_REG bits ($5001)
STATUS_DB3      EQU $08         ; bit 3 - command pending from main Z80
STATUS_DB2      EQU $04         ; bit 2 - EPORT2 latched bit

; Sound board diagnostics ROM socket (unpopulated on production)
SND_DIAG_ROM    EQU $E000

;------------------------------------------------------------------------
; AY-3-8910 register offsets (apply to all four AY chips)
;------------------------------------------------------------------------
TonA            EQU 0           ; channel A tone period (lo, hi at +1)
TonB            EQU 2           ; channel B
TonC            EQU 4           ; channel C
Noise           EQU 6           ; noise period (5-bit)
Mixer           EQU 7           ; tone/noise enable per channel (active low)
AmplA           EQU 8           ; channel A amplitude / envelope enable
AmplB           EQU 9
AmplC           EQU 10
Env             EQU 11          ; envelope period (lo, hi at +1)
EnvTp           EQU 13          ; envelope shape


;========================================================================
; Diagnostic ROM work RAM allocation map ($8000-$87FF)
;
;   This section is specific to the diagnostic ROM and conflicts with any
;   game project that owns its own RAM allocation. To skip it, define
;   TAISJ_SKIP_DIAG_RAM before INCLUDE'ing this file.
;
;   ALWAYS update this map when adding new variables - the goal is that no
;   address is ever assigned twice. Contiguous ranges are listed with their
;   owner; gaps are explicitly marked RESERVED.
;
;   Layout summary:
;     $8000-$8002  RESERVED (3 bytes)
;     $8003        SPH_SKIP
;     $8004-$8009  Menu state (6 bytes)
;     $800A-$8015  Register shadow block (12 bytes)
;     $8016        RIPPLE_PHASE2
;     $8017        TITLE_TILE_IDX (init scratch)
;     $8018-$8019  RESERVED (2 bytes)
;     $801A-$801E  Misc state (5 bytes)
;     $801F-$802E  SPRITE_MSG (16 bytes)
;     $802F-$805F  RESERVED (49 bytes)
;     $8060-$806C  Hitbus test state (13 bytes)
;     $806D-$806F  RESERVED (3 bytes)
;     $8070-$8081  VRAM test state (18 bytes)
;     $8082-$87FD  RESERVED (1916 bytes)
;     $87FE        STACK_TOP (stack grows downward)
;========================================================================

        IFNDEF  TAISJ_SKIP_DIAG_RAM

;------------------------------------------------------------------------
; $8003 : Scroll update frame skip counter
;------------------------------------------------------------------------
SPH_SKIP        EQU $8003       ; frame skip counter for scroll updates

;------------------------------------------------------------------------
; $8004-$8009 : Menu state (6 bytes)
;------------------------------------------------------------------------
MENU_STATE      EQU $8004       ; 0=SELECT 1=EDIT
MENU_CURSOR     EQU $8005       ; selected item (0-15)
MENU_TOP        EQU $8006       ; topmost visible item
MENU_NIBBLE     EQU $8007       ; 0=high nibble active, 1=low
MENU_EDIT_VAL   EQU $8008       ; value being edited
MENU_PREV_IN    EQU $8009       ; previous raw input (edge detect)

;------------------------------------------------------------------------
; $800A-$8015 : Register shadow block (12 bytes, contiguous)
;
;   Each shadow holds the last value written to its hardware register.
;   The menu reads/writes these; the IRQ handler pushes them out to the
;   real registers. Order matters - the menu indexes into this block.
;------------------------------------------------------------------------
REG_SHADOW_BASE EQU $800A
SHADOW_SMD12    EQU $800A       ; index  0 - SMD12    ($D506)
SHADOW_SMD3     EQU $800B       ; index  1 - SMD3     ($D507)
SHADOW_SOFF     EQU $800C       ; index  2 - SOFF     ($D600)
SHADOW_PRIOR    EQU $800D       ; index  3 - PRIORITY ($D300)
SHADOW_EP1      EQU $800E       ; index  4 - EPORT1   ($D50B)
SHADOW_EP2      EQU $800F       ; index  5 - EPORT2   ($D50C)
SHADOW_SPH1     EQU $8010       ; index  6 - SPH1     ($D500)
SHADOW_SPV1     EQU $8011       ; index  7 - SPV1     ($D501)
SHADOW_SPH2     EQU $8012       ; index  8 - SPH2     ($D502)
SHADOW_SPV2     EQU $8013       ; index  9 - SPV2     ($D503)
SHADOW_SPH3     EQU $8014       ; index 10 - SPH3     ($D504)
SHADOW_SPV3     EQU $8015       ; index 11 - SPV3     ($D505)

;------------------------------------------------------------------------
; $8016 : Animation state
;------------------------------------------------------------------------
RIPPLE_PHASE2   EQU $8016       ; second ripple effect phase

;------------------------------------------------------------------------
; $8017 : Title pattern fill - init scratch (used once during MAIN startup)
;------------------------------------------------------------------------
TITLE_TILE_IDX  EQU $8017       ; colour tile index 0-6 during title pattern fill

;------------------------------------------------------------------------
; $801A-$801E : Misc state (5 bytes)
;------------------------------------------------------------------------
MENU_DRAW_IDX   EQU $801A       ; current menu item being drawn
RIPPLE_PHASE    EQU $801B       ; primary ripple effect phase
SPRITE_PHASE    EQU $801C       ; sprite animation phase
SPRITE_IDX      EQU $801D       ; sprite index counter
SCROLLX         EQU $801E       ; horizontal pixel counter for layer 1

;------------------------------------------------------------------------
; $801F-$802E : Sprite message (16 bytes)
;
;   Tile indices for each of the 16 demo sprites that spell out a message.
;------------------------------------------------------------------------
SPRITE_MSG      EQU $801F

;------------------------------------------------------------------------
; $8060-$806C : Hitbus test state (13 bytes) - hitbus_test.asm
;------------------------------------------------------------------------
HT_ACTIVE       EQU $8060       ; 1 = hitbus test running
HT_TEST_X       EQU $8061       ; current test sprite X
HT_PHASE        EQU $8062       ; 0=sweeping 1=done
HT_H0X          EQU $8063       ; latched H0X
HT_H1X          EQU $8064       ; latched H1X
HT_H2X          EQU $8065       ; latched H2X
HT_HOBJ         EQU $8066       ; latched HOBJ
HT_RES_H0X      EQU $8067       ; accumulated H0X hits
HT_RES_H1X      EQU $8068       ; accumulated H1X hits
HT_RES_H2X      EQU $8069       ; accumulated H2X hits
HT_RES_HOBJ     EQU $806A       ; accumulated HOBJ layer hits (bits 2:0)
HT_ROW          EQU $806B       ; current sprite row being swept (0-2)
HT_FLIP_STATE   EQU $806C       ; persistent HFLIP/VFLIP bits driven by joystick

;------------------------------------------------------------------------
; $8070-$8081 : VRAM test state (18 bytes) - vram_test.asm
;------------------------------------------------------------------------
VT_PLANE        EQU $8070
VT_ROW          EQU $8071
VT_PAT_IDX      EQU $8072
VT_COL          EQU $8073
VT_RESULT       EQU $8074
VT_PASS         EQU $8075
VT_PASS_HI      EQU $8076
VT_FAIL         EQU $8077
VT_FAIL_HI      EQU $8078
;               $8079-$807C reserved (was VT_LAST_FAIL_P/R/W/G, removed)
VT_PAT_TABLE    EQU $807D       ; 4 bytes : $807D-$8080
VT_HOBJ_LIVE    EQU $8081       ; live HOBJ value for display

        ENDIF   ; TAISJ_SKIP_DIAG_RAM


        ENDIF   ; TAISJ_HW_INC
