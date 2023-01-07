#pragma once

#include <array>
#include <string>
#include "Block.h"
class BlockHelper
{
	public:
		BlockHelper() = delete;
	

	private:
		const std::array<uint16_t, 8>& GetBlockTexture(BlockType block_type);
		const std::string& GetBlockName(BlockType block_type);
		const std::string& GetBlockSoundPath(BlockType type);

};