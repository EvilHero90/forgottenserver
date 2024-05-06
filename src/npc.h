// Copyright 2023 The Forgotten Server Authors. All rights reserved.
// Use of this source code is governed by the GPL-2.0 License that can be found in the LICENSE file.

#ifndef FS_NPC_H
#define FS_NPC_H

#include "creature.h"
#include "luascript.h"

class Npc;
class Player;

class NpcScriptInterface final : public LuaScriptInterface
{
public:
	NpcScriptInterface();

	bool loadNpcLib(const std::string& file);

private:
	void registerFunctions();

	static int luaActionSay(lua_State* L);
	static int luaActionMove(lua_State* L);
	static int luaActionMoveTo(lua_State* L);
	static int luaActionTurn(lua_State* L);
	static int luaActionFollow(lua_State* L);
	static int luagetDistanceTo(lua_State* L);
	static int luaSetNpcFocus(lua_State* L);
	static int luaGetNpcCid(lua_State* L);
	static int luaGetNpcParameter(lua_State* L);
	static int luaOpenShopWindow(lua_State* L);
	static int luaCloseShopWindow(lua_State* L);
	static int luaDoSellItem(lua_State* L);

	// metatable
	static int luaNpcGetParameter(lua_State* L);
	static int luaNpcSetFocus(lua_State* L);

	static int luaNpcOpenShopWindow(lua_State* L);
	static int luaNpcCloseShopWindow(lua_State* L);

private:
	bool initState() override;
	bool closeState() override;

	bool libLoaded;
};

class NpcEventsHandler
{
public:
	NpcEventsHandler(const std::string& file, Npc* npc);
	NpcEventsHandler();

	void onCreatureAppear(Creature* creature);
	void onCreatureDisappear(Creature* creature);
	void onCreatureMove(Creature* creature, const Position& oldPos, const Position& newPos);
	void onCreatureSay(Creature* creature, SpeakClasses, const std::string& text);
	void onPlayerTrade(Player* player, int32_t callback, uint16_t itemId, uint8_t count, uint16_t amount,
	                   bool ignore = false, bool inBackpacks = false);
	void onPlayerCloseChannel(Player* player);
	void onPlayerEndTrade(Player* player);
	void onThink();

	void setNpc(Npc* n) { npc = n; };

	bool isLoaded() const;

	int32_t creatureAppearEvent = -1;
	int32_t creatureDisappearEvent = -1;
	int32_t creatureMoveEvent = -1;
	int32_t creatureSayEvent = -1;
	int32_t playerCloseChannelEvent = -1;
	int32_t playerEndTradeEvent = -1;
	int32_t thinkEvent = -1;

private:
	Npc* npc;
	bool loaded = false;
};

class NpcType
{
	struct NpcTypeInfo
	{
		uint8_t speechBubble = SPEECHBUBBLE_NONE;

		uint32_t walkTicks = 1500;
		uint32_t baseSpeed = 100;

		int32_t masterRadius;

		bool floorChange = false;
		bool attackable = false;
		bool ignoreHeight = false;
		bool loaded = false;
		bool isIdle = true;
		bool pushable = true;

		Outfit_t defaultOutfit;

		std::map<std::string, std::string> parameters;
	};

public:
	explicit NpcType();
	~NpcType();

	// non-copyable
	NpcType(const NpcType&) = delete;
	NpcType& operator=(const NpcType&) = delete;

	auto& getScriptInterface() { return scriptInterface; }

	bool loadCallback(NpcScriptInterface* scriptInterface);

	void setSpeechBubble(uint8_t bubble) { info.speechBubble = bubble; };
	uint8_t getSpeechBubble() { return info.speechBubble; };
	void setWalkTicks(uint32_t ticks) { info.walkTicks = ticks; };
	uint32_t getWalkTicks() { return info.walkTicks; };
	void setBaseSpeed(uint32_t speed) { info.baseSpeed = speed; };
	uint32_t getBaseSpeed() { return info.baseSpeed; };
	void setMasterRadius(int32_t radius) { info.masterRadius = radius; };
	int32_t getMasterRadius() { return info.masterRadius; };
	void setFloorChange(bool b) { info.floorChange = b; };
	bool getFloorChange() { return info.floorChange; };
	void setAttackable(bool b) { info.attackable = b; };
	bool getAttackable() { return info.attackable; };
	void setIgnoreHeight(bool b) { info.ignoreHeight = b; };
	bool getIgnoreHeight() { return info.ignoreHeight; };
	void setIsIdle(bool b) { info.isIdle = b; };
	bool getIsIdle() { return info.isIdle; };
	void setPushable(bool b) { info.pushable = b; };
	bool getPushable() { return info.pushable; };
	void setDefaultOutfit(Outfit_t outfit) { info.defaultOutfit = outfit; };
	Outfit_t getDefaultOutfit() { return info.defaultOutfit; };
	void setParameter(std::string key, std::string value) { info.parameters[key] = value; };
	std::map<std::string, std::string> getParameters() { return info.parameters; };
	void setName(std::string n) { name = n; };
	std::string getName() { return name; };

	std::string name;
	std::string filename;
	std::string eventType;

	NpcTypeInfo info;
	std::unique_ptr<NpcScriptInterface> scriptInterface;
	std::shared_ptr<NpcEventsHandler> npcEventHandler;

	friend class NpcScriptInterface;
};

class Npcs
{
public:
	static void reload();
	void addNpcType(const std::string& name, NpcType* npcType) { npcTypes[name] = npcType; }
	void clearNpcTypes() { npcTypes.clear(); }
	std::map<const std::string, NpcType*> getNpcTypes() { return npcTypes; }
	NpcType* getNpcType(std::string name);

	std::map<const std::string, NpcType*> npcTypes;

	friend class NpcType;
};

class Npc final : public Creature
{
public:
	explicit Npc(const std::string& name);
	~Npc();

	// non-copyable
	Npc(const Npc&) = delete;
	Npc& operator=(const Npc&) = delete;

	using Creature::onWalk;

	Npc* getNpc() override { return this; }
	const Npc* getNpc() const override { return this; }

	bool isPushable() const override { return pushable && walkTicks != 0; }

	void setID() override
	{
		if (id == 0) {
			id = ++npcAutoID;
		}
	}

	void removeList() override;
	void addList() override;

	static Npc* createNpc(const std::string& name);

	bool canSee(const Position& pos) const override;

	bool load();
	void reload();
	void reset();

	const std::string& getName() const override { return name; }
	void setName(const std::string& n) { name = n; }
	const std::string& getNameDescription() const override { return name; }
	const std::string& getEventType() { return eventType; }
	void setEventType(const std::string& event) { eventType = event; }

	CreatureType_t getType() const override { return CREATURETYPE_NPC; }

	uint8_t getSpeechBubble() const override { return speechBubble; }
	void setSpeechBubble(const uint8_t bubble) { speechBubble = bubble; }

	void doSay(const std::string& text);
	void doSayToPlayer(Player* player, const std::string& text);

	bool doMoveTo(const Position& pos, int32_t minTargetDist = 1, int32_t maxTargetDist = 1, bool fullPathSearch = true,
	              bool clearSight = true, int32_t maxSearchDist = 0);

	int32_t getMasterRadius() const { return masterRadius; }
	const Position& getMasterPos() const { return masterPos; }
	void setMasterPos(Position pos, int32_t radius = 1)
	{
		masterPos = pos;
		if (masterRadius == -1) {
			masterRadius = radius;
		}
	}

	void onPlayerCloseChannel(Player* player);
	void onPlayerTrade(Player* player, int32_t callback, uint16_t itemId, uint8_t count, uint16_t amount,
	                   bool ignore = false, bool inBackpacks = false);
	void onPlayerEndTrade(Player* player, int32_t buyCallback, int32_t sellCallback);

	void turnToCreature(Creature* creature);
	void setCreatureFocus(Creature* creature);

	auto& getScriptInterface() { return npcType->scriptInterface; }

	static uint32_t npcAutoID;

	const auto& getSpectators() { return spectators; }

	void loadNpcTypeInfo();

	std::shared_ptr<NpcEventsHandler> npcEventHandler;
	bool fromLua = false;
	NpcType* npcType;

private:
	void onCreatureAppear(Creature* creature, bool isLogin) override;
	void onRemoveCreature(Creature* creature, bool isLogout) override;
	void onCreatureMove(Creature* creature, const Tile* newTile, const Position& newPos, const Tile* oldTile,
	                    const Position& oldPos, bool teleport) override;

	void onCreatureSay(Creature* creature, SpeakClasses type, const std::string& text) override;
	void onThink(uint32_t interval) override;
	std::string getDescription(int32_t lookDistance) const override;

	bool isImmune(CombatType_t) const override { return !attackable; }
	bool isImmune(ConditionType_t) const override { return !attackable; }
	bool isAttackable() const override { return attackable; }
	bool getNextStep(Direction& dir, uint32_t& flags) override;

	void setIdle(const bool idle);

	bool canWalkTo(const Position& fromPos, Direction dir) const;
	bool getRandomStep(Direction& direction) const;

	bool loadFromXml();

	void addShopPlayer(Player* player);
	void removeShopPlayer(Player* player);
	void closeAllShopWindows();

	std::map<std::string, std::string> parameters;

	std::set<Player*> shopPlayerSet;
	std::set<Player*> spectators;

	std::string name;
	std::string filename;
	std::string eventType;

	Position masterPos;

	uint32_t walkTicks;
	uint32_t baseSpeed;
	int32_t focusCreature;
	int32_t masterRadius;

	uint8_t speechBubble;

	bool floorChange;
	bool attackable;
	bool ignoreHeight;
	bool loaded;
	bool isIdle;
	bool pushable;

	friend class Npcs;
	friend class NpcType;
	friend class NpcScriptInterface;
};

#endif // FS_NPC_H
