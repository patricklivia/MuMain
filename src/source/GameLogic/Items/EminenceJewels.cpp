#include "stdafx.h"
#include "GameLogic/Items/EminenceJewels.h"

#include "GameLogic/Items/ItemCategories.h"

namespace
{
constexpr int MaxLevelByJewel = 13;

bool IsWeaponOrShield(int type)
{
    return type >= ITEM_SWORD && type < ITEM_HELM;
}

bool IsSetPart(int type)
{
    return type >= ITEM_HELM && type < ITEM_WING;
}

bool IsRingOrPendant(int type)
{
    switch (type)
    {
    case ITEM_RING_OF_ICE:
    case ITEM_RING_OF_POISON:
    case ITEM_PENDANT_OF_LIGHTING:
    case ITEM_PENDANT_OF_FIRE:
    case ITEM_WIZARDS_RING:
    case ITEM_RING_OF_FIRE:
    case ITEM_RING_OF_EARTH:
    case ITEM_RING_OF_WIND:
    case ITEM_RING_OF_MAGIC:
    case ITEM_PENDANT_OF_ICE:
    case ITEM_PENDANT_OF_WIND:
    case ITEM_PENDANT_OF_WATER:
    case ITEM_PENDANT_OF_ABILITY:
        return true;
    default:
        return false;
    }
}

bool IsWingOrCape(const ITEM* pItem)
{
    return GameLogic::Items::IsWingItem(pItem) || pItem->Type == ITEM_CAPE_OF_LORD;
}

bool IsPet(const ITEM* pItem)
{
    return pItem->Type >= ITEM_HELPER && pItem->Type < ITEM_HELPER + MAX_ITEM_INDEX &&
           GameLogic::Items::IsPetSlotModel(pItem->Type + MODEL_ITEM);
}
} // namespace

namespace GameLogic::Items::Eminence
{
    bool IsEnhancementJewelType(int itemType)
    {
        return itemType >= ITEM_POTION + JewelOfLevelNumber && itemType <= ITEM_POTION + JewelOfVisualNumber;
    }

    bool IsEnhancementJewel(const ITEM* pItem)
    {
        return pItem != nullptr && IsEnhancementJewelType(pItem->Type);
    }

    bool CanApplyEnhancementJewel(const ITEM* pJewel, const ITEM* pTarget)
    {
        if (!IsEnhancementJewel(pJewel) || pTarget == nullptr || IsEnhancementJewel(pTarget))
        {
            return false;
        }

        const int type = pTarget->Type;
        if (IsAmmunition(pTarget))
        {
            return false;
        }

        const bool weaponOrShield = IsWeaponOrShield(type);
        const bool setPart = IsSetPart(type);
        const bool ringOrPendant = IsRingOrPendant(type);
        const bool wingOrCape = IsWingOrCape(pTarget);

        switch (pJewel->Type - ITEM_POTION)
        {
        case JewelOfLevelNumber:
            return (weaponOrShield || setPart || ringOrPendant || wingOrCape) && pTarget->Level < MaxLevelByJewel;
        case JewelOfAdditionalNumber:
            return weaponOrShield || setPart || ringOrPendant || wingOrCape;
        case JewelOfExcellentNumber:
            return weaponOrShield || setPart || ringOrPendant;
        case JewelOfSkillNumber:
            return weaponOrShield;
        case JewelOfFullNumber:
            return weaponOrShield || setPart || wingOrCape;
        case JewelOfVisualNumber:
            return weaponOrShield || setPart || wingOrCape || IsPet(pTarget);
        default:
            return false;
        }
    }
} // namespace GameLogic::Items::Eminence
