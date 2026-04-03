# Beta 1.7.3 Protocol — Data Structures

## Basic Types

All multi-byte values are **big-endian**.

| Type | Size | Range | Notes |
|------|------|-------|-------|
| `byte` | 1 byte | -128 to 127 | Signed |
| `short` | 2 bytes | -32768 to 32767 | Signed |
| `int` | 4 bytes | -2147483648 to 2147483647 | Signed |
| `long` | 8 bytes | -2⁶³ to 2⁶³-1 | Signed |
| `float` | 4 bytes | IEEE 754 | Single precision |
| `double` | 8 bytes | IEEE 754 | Double precision |
| `bool` | 1 byte | `0x00` / `0x01` | false / true |

---

## Compound Types

### String

A length-prefixed UTF-16BE string.

```
short    length     ← number of characters (not bytes)
char[]   data       ← UTF-16BE, 2 bytes per character
```

**Example:** `"MrDeun"` (6 characters)
```
00 06  4d 72 44 65 75 6e  →  "MrDeun"
^      ^ UTF-16BE chars
length
```

> ⚠️ Length is character count, not byte count. Total bytes = `2 + (length × 2)`.

---

### Item / Slot

Used in inventory packets. The count and damage fields are only present if the item is not empty.

```
short    item_id     ← -1 means empty slot
byte     count       ← only present if item_id != -1
short    damage      ← only present if item_id != -1
```

**Empty slot:**
```
ff ff
```

**A stack of 64 stone (id=1):**
```
00 01   40   00 00
^id=1  ^64  ^damage=0
```

---

### Entity Metadata

A stream of typed key-value pairs terminated by `0x7F`. Used to describe entity state (health, fire ticks, etc).

```
byte     key_and_type    ← bits [7..5] = type, bits [4..0] = index
<value>                  ← type determines what follows:
                            0 → byte
                            1 → short
                            2 → int
                            3 → float
                            4 → string
                            5 → item/slot
...      (more entries)
byte     0x7F            ← end of metadata marker
```

**Example:**
```
00       ← type=0 (byte), index=0
48       ← value: 0x48 = 72
7f       ← end marker
```

---

## What Does NOT Exist in This Protocol

Unlike modern Minecraft, Beta 1.7.3 has **no**:

- `VarInt` / `VarLong` — all integers are fixed-size
- Packet length prefix — you parse by packet ID, not by length
- Encryption — all traffic is plaintext
- Compression — all traffic is uncompressed
- UUIDs — players identified by username only
- NBT in the base protocol — NBT only appears inside raw chunk data (`0x33`)
- Optional fields — every field is always present (except item slot count/damage)
- State machine — there is only one connection state throughout