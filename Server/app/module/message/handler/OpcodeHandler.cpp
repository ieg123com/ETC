#include "OpcodeHandler.h"

namespace Hotfix
{
	bool OpcodeHandler::IsOuterMassage(const uint16_t opcode)
	{
		// 20000 ���µ���Ϣid,���Ƿ�������ͨ�ŵ��ڲ���Ϣid
		return (20000 <= opcode);
	}
}


