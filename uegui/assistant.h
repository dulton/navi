#ifndef _UEGUI_ASSISTANT_H
#define _UEGUI_ASSISTANT_H
class CAssistant {
public:
  //�ж�4S�;������ݵ������Ƿ�����Ŀ������
  //4S�;�������������ʮ���Ƶ���Ҫ����ת��
  static bool IsBelongTo(int src, int dest)
  {
    //����ת������ʹ��24λ�Ķ���������ʾ�����λ�ǵ�������
    unsigned int first = src / 10000;
    unsigned int two = (src % 10000) / 100;
    unsigned int last = src  % 100;
    first = first << 16;
    two = two << 8;
    unsigned int result = first | two | last;
    //(dest & 0x0000ff) == 0 ��ʾdest���м������ϵġ���ֻҪ�Ƚ��Ǽ������ϵı���
    if ( result == dest ||
      ((dest & 0x0000ff) == 0 && (result & 0xffff00) == (dest & 0xffff00) )
      || ((dest == 720896) && (result & 0xff0000) == (dest & 0xff0000)) //������
      || ((dest == 786432) && (result & 0xff0000) == (dest & 0xff0000)) //�����
      || ((dest == 2031616) && (result & 0xff0000) == (dest & 0xff0000)) //�Ϻ���
      || ((dest == 5308416) && (result & 0xff0000) == (dest & 0xff0000))  //���
      || ((dest == 5373952) && (result & 0xff0000) == (dest & 0xff0000)))  //����
    {
      return true;
    }
    return false;
  }
};
#endif