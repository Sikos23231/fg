// Copyright 2023 The Forgotten Server Authors. All rights reserved.
// Use of this source code is governed by the GPL-2.0 License that can be found in the LICENSE file.

#ifndef FS_PARTY_H
#define FS_PARTY_H

class Player;

class Party
{
public:
	Player* leader;

	std::vector<Player*> members;
	std::vector<Player*> invitees;

	struct
	{
		bool active = false;
		bool enabled = false;
		std::map<Player*, int64_t> attackTicks;
	} sharedExperience;
};

#endif // FS_PARTY_H
