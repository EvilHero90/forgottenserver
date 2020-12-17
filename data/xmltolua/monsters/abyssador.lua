local mtype = Game.createMonsterType("abyssador")
local monster = {}
monster.description = "abyssador"
monster.experience = 50000
monster.outfit = {
	lookType = 495
}

monster.health = 300000
monster.maxHealth = monster.health
monster.race = "blood"
monster.corpse = 17413
monster.speed = 470
monster.runHealth = 100
monster.maxSummons = 0

monster.changeTarget = {
    interval = 5000,
	chance = 8
}

monster.flags = {
	healthHidden = false,
	summonable = false,
    attackable = true,
	hostile = true,
	convinceable = false,
    illusionable = false,
	canPushItems = true,
	canPushCreatures = true,
	targetDistance = 1,
	staticAttack = 50
}

monster.voices = {
	interval = 3000,
	chance = 10,
	{text = "*** BRAINS *** SMALL ***", yell = false},
	{text = "*** LIVE *** DRY ***", yell = false},
	{text = "*** IMPORTANT ***", yell = false},
	{text = "*** FIRE *** HOME *** VICTORY ***", yell = false},
	{text = "*** EXISTENCE *** FUTILE ***", yell = false},
	{text = "*** TIME ***", yell = false},
	{text = "*** STEALTH ***", yell = false},
	{text = "*** DEATH ***", yell = false}
}

monster.loot = {
    {id = 18449 --[[decorative ribbon]], chance = 10000},
	{id = 18450 --[[crystalline sword]], chance = 5500},
	{id = 18451 --[[crystalline axe]], chance = 5500},
	{id = 18452 --[[mycological mace]], chance = 4500},
	{id = 18453 --[[crystal crossbow]], chance = 4500},
	{id = 18454 --[[mycological bow]], chance = 10000},
	{id = 18465 --[[shiny blade]], chance = 8000},
	{id = 18496 --[[Abyssador's lash]], chance = 100000}
}

monster.attacks = {
	{name = "melee",  attack = 0, skill = 0, minDamage = 0, maxDamage = -960, interval = 2500},
	{name = "speed",  chance = 20, interval = 2000, minDamage = 0, maxDamage = 0, range = 7},
	{name = "combat", type = COMBAT_FIREDAMAGE,  chance = 10, interval = 800, minDamage = -820, maxDamage = -1250, range = 7},
	{name = "combat", type = COMBAT_ENERGYDAMAGE,  chance = 10, interval = 750, minDamage = -650, maxDamage = -1300, range = 3},
	{name = "combat", type = COMBAT_LIFEDRAIN,  chance = 10, interval = 700, minDamage = -600, maxDamage = -1230, range = 3},
	{name = "combat", type = COMBAT_EARTHDAMAGE,  chance = 12, interval = 700, minDamage = -40, maxDamage = -130, range = 0}
}

monster.defenses = {
	defense = 20,
    armor = 15,
    {name = "combat", type = COMBAT_HEALING,  chance = 1, interval = 1000, minDamage = 0, maxDamage = 300000, range = 0},
	{name = "combat", type = COMBAT_HEALING,  chance = 30, interval = 5000, minDamage = 1000, maxDamage = 1000, range = 0},
	{name = "invisible",  chance = 25, interval = 2000, minDamage = 0, maxDamage = 0, range = 0}
}

monster.elements = {
    {type = COMBAT_PHYSICALDAMAGE, percent = 10},
	{type = COMBAT_ENERGYDAMAGE, percent = -20},
	{type = COMBAT_DEATHDAMAGE, percent = -20}
}

monster.immunities = {
	{type = "drown", condition = true, combat = true},
	{type = "lifedrain", condition = false, combat = false},
	{type = "paralyze", condition = true, combat = false},
	{type = "drunk", condition = true, combat = false},
	{type = "poison", condition = true, combat = true},
	{type = "cursed", condition = false, combat = false},
	{type = "invisible", condition = true, combat = false},
	{type = "outfit", condition = true, combat = false},
	{type = "manadrain", condition = false, combat = false},
	{type = "manashield", condition = false, combat = false},
	{type = "freezing", condition = false, combat = false},
	{type = "energy", condition = false, combat = false},
	{type = "undefined", condition = false, combat = false},
	{type = "physical", condition = false, combat = false},
	{type = "haste", condition = false, combat = false},
	{type = "healing", condition = false, combat = false},
	{type = "light", condition = false, combat = false},
	{type = "death", condition = false, combat = false},
	{type = "ice", condition = false, combat = false},
	{type = "infight", condition = false, combat = false},
	{type = "fire", condition = false, combat = false},
	{type = "holy", condition = false, combat = false}
}

mtype:register(monster)