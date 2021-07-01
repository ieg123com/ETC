/**
  * @file     	test.h
  * @author   	JonesLee
  * @email   	Jones_Lee3@163.com
  * @version	V4.01
  * @date    	07-DEC-2017
  * @license  	GNU General Public License (GPL)  
  * @brief   	Universal Synchronous/Asynchronous Receiver/Transmitter 
  * @detail		detail
  * @attention
  *  This file is part of OST.                                                  \n                                                                  
  *  This program is free software; you can redistribute it and/or modify 		\n     
  *  it under the terms of the GNU General Public License version 3 as 		    \n   
  *  published by the Free Software Foundation.                               	\n 
  *  You should have received a copy of the GNU General Public License   		\n      
  *  along with OST. If not, see <http://www.gnu.org/licenses/>.       			\n  
  *  Unless required by applicable law or agreed to in writing, software       	\n
  *  distributed under the License is distributed on an "AS IS" BASIS,         	\n
  *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  	\n
  *  See the License for the specific language governing permissions and     	\n  
  *  limitations under the License.   											\n
  *   																			\n
  * @htmlonly 
  * <span style="font-weight: bold">History</span> 
  * @endhtmlonly 
  * Version|Auther|Date|Describe
  * ------|----|------|-------- 
  * V3.3|Jones Lee|07-DEC-2017|Create File
  * <h2><center>&copy;COPYRIGHT 2017 WELLCASA All Rights Reserved.</center></h2>
  */  
#pragma once


/** @brief 类"Test"*/
class Test
{
public:
    /** @brief A enum, with inline docs 测试 */
    enum TEnum 
    {
        TVal1, /**< enum value TVal1. */ 
        TVal2, /**< enum value TVal2. */ 
        TVal3 /**< enum value TVal3. */ 
    } 
   *enumPtr, /**< enum pointer. */
    enumVar; /**< enum variable. */
    /** @brief A constructor. */ 
Test(); 
/** @brief A destructor. */ 
~Test();
 /** 
  * @brief      a normal member taking two arguments and returning an integer value. 
  * @param[in]  a : 输入变量'a'
  * @param[in]  s : 输入变量's'
  * @return
  *     -1 失败
  *     0  成功
  *     1  完成
  * @par Sample
  * @code
  *	u8 p[8] = {0};
  *	res_ res = 0; 
  * 	res = can_send_msg(CAN1,1,p,0x11,8,1);
  * @endcode
  * */ 
    int testMe(int a,const char *s); 
};



/**
    * @brief		can send the message
    * @param[in]	canx : The Number of CAN
    * @param[in]	id : the can id	
    * @param[in]	p : the data will be sent
    * @param[in]	size : the data size
    * @param[in]	is_check_send_time : is need check out the time out
    * @note	Notice that the size of the size is smaller than the size of the buffer.		
    * @return		
    *	+1 Send successfully \n
    *	-1 input parameter error \n
    *	-2 canx initialize error \n
    *	-3 canx time out error \n
    * @par Sample
    * @code
    *	u8 p[8] = {0};
    *	res_ res = 0; 
    * 	res = can_send_msg(CAN1,1,p,0x11,8,1);
    * @endcode
    */							
s32 can_send_msg(const CAN_TypeDef * canx,
                        const u32 id,
                        const u8 *p,
                        const u8 size,
                        const u8 is_check_send_time);
