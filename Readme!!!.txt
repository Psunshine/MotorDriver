/*******************************Copyright (c)***********************************
  *                      ������ͨ��ѧRobocon2015������С��
  ******************************************************************************
  * @�ļ�	Readme!!!.txt
  * @����	2015-2-14
  * @˵��	˵���ĵ�
  ******************************************************************************
  * ������ͨ��ѧ-ͨ��1208-��С��
  *
  * ˵��:	IAR�汾:7.20.2.7314
  *      	���ļ��汾:��׼�� V1.3.0
  * �ļ�����:	Tab Size:4
  * �Զ�����:	Body:4          
  * ��ϸ˵����Documents��Readme.txt
  ******************************************************************************
  */
  
����˵����
      1���˹���ʹ��IAR7.20.2.7314�汾������ʹ��IAR7.20.2.7314�����ϰ汾�򿪡�
      2���˹��̿��ļ��汾ΪSTM32F4XX��׼�� V1.3.0��
      3����ʽ˵����
	     Tools -> Options -> Editor
		      Tab Size����Ϊ4��Indent Size����Ϊ4����ѡInsert Tab
	     Tools -> Options -> Editor�Ҳ���Configure
		      Body����Ϊ4��
	  4����ĿOptions -> C/C++ Compiler -> Preprocessor
	     (1)Additional include directories:
		    $PROJ_DIR$\USER
		    $PROJ_DIR$\APP
		    $PROJ_DIR$\CMSIS
		    $PROJ_DIR$\FWLib\inc
		    $PROJ_DIR$\FWLib\src
		    $PROJ_DIR$\BSP\inc
		 (2)Defined Symbols:
		    STM32F40XX
		    USE_STDPERIPH_DRIVER
		    ARM_MATH_CM4
	   5��������FPU -> VFPv4

Workspace�ṹ˵����
      1��BSP(Board Support Package)�ǰ弶֧�ְ�������ΪһЩ������������
      2��App(Ӧ�ò�)������ҪΪһЩ�㷨���ϲ�ʵ�֡�
      3��CM4��Ϊϵͳ��ʼ�����ã���Ҫ��㶯��
      4��Documents��Ϊ˵����һЩST�ٷ���ʹ���ֲᣬ������һ�𷽱���ҡ�
      5��DSP_LibΪ���ARM Cortex-M4�ں˵�DSP�⡣����arm_math.hʹ��DSP���еĺ���
         ��ֱ��ʹ��math.h�ٶȸ��죬Ч�ʸ��ߡ������ļ��϶࣬�����ռ�ÿռ��
         Ĭ�ϲ��õ�ͳͳ����UnCompile�С�����ʹ�÷����μ�ST�ٷ�������Examples��
         (1)Complie��Ϊ���������ļ���
         (2)UuCompile��Ϊ�����������ļ���
      5��FWLib��Ϊ��׼�̼��⡣Ϊ�˼ӿ�����ٶȣ�������Compile��UnCompile��
         (1)Complie��Ϊ���������ļ���
         (2)UuCompile��Ϊ�����������ļ���
      6��Startup��ΪSTM32�����Ļ����롣
      7��OutputΪ�������ɵ��ļ���
      8�����̸�·����Ϊͨ���ļ���
	  
����ṹ˵����
      1��BSP��ÿһ��.c��.h�ļ���Ӧһ�����衣����һ���ṹ�������
      2��һ�����̶���һ���ܵĽṹ����������г�ԱΪ���������Ӧ����Ҫʹ�õı�����
      3�������ܵĽṹ�������ʹ��ָ��ָ������ļ��еĽṹ�塣
	  
�ļ��ṹ˵����
      CMSIS(Cortex ΢����������ӿڱ�׼)
	        startup -> startup_stm32f40_41xxx.s ������������
	        core_cm4.h ��Cortex-M4ȫ�������Ͷ��壬��̬��������
	        core_cm4_simd.h ��Cortex-M4��ָ���������(simd)���Ż�����Ϊ��
	        stm32f4xx.h ����������ͷ�ļ�
	        system_stm32f4xx.c ���豸���嶨��
	        system_stm32f4xx.h ���豸�ض�������
			arm_math.h :DSP��ͷ�ļ�����
	       *core_cmFunc.h ��Cortex-M�ں˹��ܷ��ʽӿ�
	       *core_cmInstr.h ��Cortex-M�ں˷���ָ��
      Config
	        stm32f40x_ram.icf:RAM�е��Ե������ļ�
	        stm32f40x_flash.icf:FLASH�е��Ե������ļ�
      FWLib(��׼�����)
	        DSP_Lib(DSP�⺯��)DSP_LibΪ���ARM Cortex-M4�ں˵�DSP�⡣
	        ����arm_math.hʹ��DSP���еĺ�����ֱ��ʹ��math.h�ٶȸ��죬Ч�ʸ��ߡ�
	        ����ʹ�÷����μ�ST�ٷ�������Examples��
      App(ϵͳӦ�ú���)
      BSP(�弶֧�ְ�)
      USER(�û����ļ�)
	        stm32f4xx_conf.h �������ļ�,��Ҫʹ��ĳһ������ʱ,�����ļ���ȡ����ע��
	        stm32f4xx_it.c ���жϺ���ģ��
	        stm32f4xx_it.h ���жϺ���ģ��
	        includes.h ��ͷ�ļ�����
	        main.c ������������
	        Sysinit.c ��ϵͳ��ʼ����������
	        Sysinit.h ��ϵͳ��ʼ����������
      Documents(�ĵ�˵��)