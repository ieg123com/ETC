#include "OpcodeHandler.h"

namespace Hotfix
{
	bool OpcodeHandler::IsOuterMassage(const uint16_t opcode)
	{
		// 20000 以下的消息id,都是服务器间通信的内部消息id
		return (20000 <= opcode);
	}
}


