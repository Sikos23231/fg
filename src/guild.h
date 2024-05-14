// Copyright 2023 The Forgotten Server Authors. All rights reserved.
// Use of this source code is governed by the GPL-2.0 License that can be found in the LICENSE file.

#ifndef FS_GUILD_H
#define FS_GUILD_H

class Player;

struct GuildRank
{
	uint32_t id;
	std::string name;
	uint8_t level;

	GuildRank(uint32_t id, std::string_view name, uint8_t level) : id{id}, name{name}, level{level} {}
};

class Guild
{
public:
	Guild(uint32_t id, std::string_view name) : name{name}, id{id} {}

	uint32_t getId() const { return id; }
	const std::string& getName() const { return name; }

	void addMember(Player* player);
	void removeMember(Player* player);
	const std::list<Player*>& getMembersOnline() const { return membersOnline; }
	uint32_t getMemberCount() const { return memberCount; }
	void setMemberCount(uint32_t count) { memberCount = count; }

	void addRank(uint32_t rankId, std::string_view rankName, uint8_t level);
	const std::vector<std::shared_ptr<GuildRank>>& getRanks() const { return ranks; }
	std::shared_ptr<GuildRank> getRankById(uint32_t rankId);
	std::shared_ptr<GuildRank> getRankByName(const std::string& name) const;
	std::shared_ptr<GuildRank> getRankByLevel(uint8_t level) const;

	const std::string& getMotd() const { return motd; }
	void setMotd(const std::string& motd) { this->motd = motd; }

private:
	std::list<Player*> membersOnline;
	std::vector<std::shared_ptr<GuildRank>> ranks;
	std::string name;
	std::string motd;
	uint32_t id;
	uint32_t memberCount = 0;
};

namespace IOGuild {
std::shared_ptr<Guild> loadGuild(uint32_t guildId);
uint32_t getGuildIdByName(const std::string& name);
}; // namespace IOGuild

#endif // FS_GUILD_H
