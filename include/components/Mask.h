#ifndef _MASK_H_
#define _MASK_H_
#include "types/Memory.h"
#include "Components.h"

/* Mask.h no sabe qué es COMPONENT_POSITION o COMPONENT_LAYOUT.
   Solo necesita que COMPONENT_COUNT exista para calcular cuántas
   palabras hacen falta. */
#define MASK_WORDS ((COMPONENT_COUNT + BITS_PER_UNIT - 1) / BITS_PER_UNIT)

typedef struct {
    fxmem_uint words[MASK_WORDS];
} ComponentMask;

extern ComponentMask Entity_Mask[MAX_ENTITIES];

#define MASK_WORD(comp) ((comp) / BITS_PER_UNIT)
#define MASK_BIT(comp)  ((fxmem_uint)1 << ((comp) % BITS_PER_UNIT))
#define MASK_SET(id, comp)    (Entity_Mask[(id)].words[MASK_WORD(comp)] |= MASK_BIT(comp))
#define MASK_CLEAR(id, comp)  (Entity_Mask[(id)].words[MASK_WORD(comp)] &= (fxmem_uint)~MASK_BIT(comp))
#define MASK_HAS(id, comp)    ((Entity_Mask[(id)].words[MASK_WORD(comp)] & MASK_BIT(comp)) != 0)

#endif