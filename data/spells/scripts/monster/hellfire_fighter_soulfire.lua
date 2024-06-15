local combat = Combat()
combat:setParameter(COMBAT_PARAM_TYPE, COMBAT_FIREDAMAGE)
combat:setParameter(COMBAT_PARAM_EFFECT, CONST_ME_FIREATTACK)
combat:setArea(createCombatArea(AREA_CIRCLE6X6))

function onCastSpell(creature, variant)
    for _, target in ipairs(combat:getTargets(creature, variant)) do
        creature:addDamageCondition(target, CONDITION_FIRE,
                                    DAMAGELIST_VARYING_PERIOD, 10, {8, 10}, 20)
    end
    return true
end
