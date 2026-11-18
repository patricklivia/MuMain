#pragma once

typedef struct tagITEM ITEM;

// Eminence MU: the six enhancement jewels (Joias de Aprimoramento), group 14, numbers 200 to 205.
// The server must define the same items and apply them when one is dropped on an item
// (70% for free accounts, 100% for VIP, the item is never lost on failure).
namespace GameLogic::Items::Eminence
{
    // Item numbers inside group 14 (ITEM_POTION).
    constexpr int JewelOfLevelNumber = 200;     // +1 level, +0 to +13
    constexpr int JewelOfAdditionalNumber = 201; // additional option (+28)
    constexpr int JewelOfExcellentNumber = 202;  // excellent option
    constexpr int JewelOfSkillNumber = 203;      // weapon skill
    constexpr int JewelOfFullNumber = 204;       // full item
    constexpr int JewelOfVisualNumber = 205;     // visual item

    bool IsEnhancementJewelType(int itemType);
    bool IsEnhancementJewel(const ITEM* pItem);
    // Whether dropping `pJewel` on `pTarget` asks the server to apply it.
    bool CanApplyEnhancementJewel(const ITEM* pJewel, const ITEM* pTarget);
} // namespace GameLogic::Items::Eminence
