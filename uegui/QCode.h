#ifndef __Q_CODE_H__
#define __Q_CODE_H__

#ifdef __cplusplus
extern "C" {
#endif

	/**
	* ��γ�� -- Q��
	*		@param	dX					[in]		����
	*		@param	dY					[in]		γ��
	*		@param	pCode				[out]		���뻺����
	*		@param	nCode				[out]		��������д
	*		@return	�ɹ�����true��ʧ�ܷ���false
	*/
	bool QCode_MapToCode( double dX, double dY, unsigned short* pCode, int nCode );

	/**
	* Q�� -- ��γ��
	*		@param	pCode				[in]		���뻺����
	*		@param	nCode				[in]		��������д
	*		@param	dX					[out]		����
	*		@param	dY					[out]		γ��
	*		@return	�ɹ�����true��ʧ�ܷ���false
	*/
	bool QCode_CodeToMap( unsigned short* pCode, int nCode, double& dX, double& dY );

#ifdef __cplusplus
}
#endif


#endif	// __Q_CODE_H__