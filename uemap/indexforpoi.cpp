/**
* Copyright (C) 2012-2013 Guangdong Ritu Information Systems Co.,Ltd.
*/

#include "indexForPoi.h"
#include "groundgate.h"

using namespace UeMap;

void CIndexForPoi::GetPoiIndex(CGroundGrid *oneGrid, std::vector<unsigned long>& poiIndexs, CGeoRect<long> mapRect)
{
  //����indexvector��ͨ��poiIndexs����
  BinaryFindPoiInMapRect(oneGrid, mapRect, poiIndexs);
}

void CIndexForPoi::BinaryFindPoiInMapRect(CGroundGrid *oneGrid, CGeoRect<long> mapRect, std::vector<unsigned long>& poiIndexs)
{
  unsigned char* poiBuf = const_cast<unsigned char*>(oneGrid->GetData());
  //�������м��
  int poiSize = 14;
  long poiNum = oneGrid->GetSize()/poiSize;  
  //poi��Ӧƫ�����Ǵ�0��ʼ
  poiNum--;

  RealGridPoi poi;  
  long ret = 0;
  long bufOffset = poiNum/2;//����ѭ������ʼ��ʱ��Ӧ�������ĵ�
  long minOffset = 0;//Сֵ
  long maxOffset = poiNum;//��ֵ

  //���ֲ��Ҹ��ڴ�飨��һ��map������бȽϣ�
  while (minOffset <= maxOffset)
  {
    //����poi������ɹ���������һ��λ��
    if (!ConstructPoi(poi, poiBuf, bufOffset*poiSize))
    {
      bufOffset++;
      if (bufOffset > maxOffset)
      {
        bufOffset = maxOffset;
        break;
      }
      continue;
    }

    //�����жϵ�ǰ�����ڷ���
    ret = IsPoiInMapRect(mapRect, poi);
    switch(ret)
    {
    case PD_Left:
      {
        //��
        minOffset = bufOffset + 1;
        bufOffset = (maxOffset + minOffset)/2;
        continue;
      }
      
    case PD_Right:
      {
        //��
        maxOffset = bufOffset-1;
        bufOffset = (maxOffset + minOffset)/2;
        continue;
      }
    case PD_Up:
      //����
    case PD_Down:
      {
        //����
        break;
      }        
    case PD_InMap:
      {
        //�м�
        poiIndexs.push_back(poi.m_offSet);
        break;
      }      
    default:
      {
        //����ֵ�򷵻�
        return;
      }
        
    }

    //retΪPD_Up,PD_Downʱ��ǰ�㲢������map�ķ�Χ��
    if (ret == PD_Up || ret == PD_Down|| ret == PD_InMap)
    {
      break;
    }
  }//end while

  //δ�ҵ��м����ֱ�ӷ���
  if (minOffset > maxOffset)
  {
    return;
  }
  //�ҵ����м����ֱ�������ұ���չ,�ҵ�poi�ͼ���poiIndexs
  int preOffset = bufOffset;

  //��ǰ����
  bufOffset--;

  while (true)
  {
    if (bufOffset < 0)
    {
      break;
    }
    ConstructPoi(poi, poiBuf, (bufOffset)*poiSize);
    ret = IsPoiInMapRect(mapRect,poi);
    if (ret == PD_InMap)
    {
      poiIndexs.push_back(poi.m_offSet);
    }
    if (ret == PD_Left || ret == PD_Right)
    {
      break;
    }
    bufOffset--; 

  }

  //�������
  bufOffset = preOffset;
  bufOffset++;

  while (true)
  {
    if (bufOffset > poiNum)
    {
      break;
    }
    ConstructPoi(poi, poiBuf, (bufOffset)*poiSize);
    ret = IsPoiInMapRect(mapRect, poi);
    if (ret == PD_InMap)
    {
      poiIndexs.push_back(poi.m_offSet);
    }
    if (ret == PD_Left || ret == PD_Right)
    {
      break;
    }

    bufOffset++; 
  }

}

int CIndexForPoi::IsPoiInMapRect(CGeoRect<long> mapRect, RealGridPoi &poi)
{
  //
  if (poi.m_x < mapRect.m_minX)
  {
    return PD_Left;//���
  }
  else if (poi.m_x > mapRect.m_maxX)
  {
    return PD_Right;//�ұ�
  }
  else if (poi.m_y < mapRect.m_minY)
  {
    return PD_Up;//����
  }
  else if (poi.m_y > mapRect.m_maxY)
  {
    return PD_Down;//����
  }
  else
  {
    return PD_InMap;//�м�
  }  

}

CIndexForPoi::CIndexForPoi()
{
}


CIndexForPoi::~CIndexForPoi()
{
}

bool CIndexForPoi::ConstructPoi(RealGridPoi& poi, unsigned char* poiBuf, unsigned long bufOffset)
{
  unsigned long x = 0;
  unsigned long y = 0;
  unsigned long indexOff = 0; 
  int cursor = 0;

  //�ӵڶ���λ�ÿ�ʼ
  cursor = 2 + bufOffset;
  poi.m_offSet = cursor - 2;

  x = y =0;
  x = *(poiBuf + cursor + 3) << 24 | *( poiBuf + cursor + 2) << 16 | *(poiBuf + cursor + 1) << 8 | *(poiBuf + cursor);  
  cursor +=4;
  y = *(poiBuf + cursor + 3) << 24 | *( poiBuf + cursor + 2) << 16 | *(poiBuf + cursor + 1) << 8 | *(poiBuf + cursor);  

  poi.m_x = x;
  poi.m_y = y;

  return true;
}

