-- -------------------------------------------------------------
-- 
-- File Name: hdlsrc\FPGA_SMC\Model.vhd
-- Created: 2020-12-13 17:04:02
-- 
-- Generated by MATLAB 9.7 and HDL Coder 3.15
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: Model
-- Source Path: FPGA_SMC/Model
-- Hierarchy Level: 1
-- 
-- System Model
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY Model IS
  PORT( w                                 :   IN    std_logic_vector(63 DOWNTO 0);  -- double
        dw                                :   OUT   std_logic_vector(63 DOWNTO 0)  -- double
        );
END Model;


ARCHITECTURE rtl OF Model IS

  ATTRIBUTE multstyle : string;

  -- Component Declarations
  COMPONENT nfp_mul_double
    PORT( nfp_in1                         :   IN    std_logic_vector(63 DOWNTO 0);  -- double
          nfp_in2                         :   IN    std_logic_vector(63 DOWNTO 0);  -- double
          nfp_out                         :   OUT   std_logic_vector(63 DOWNTO 0)  -- double
          );
  END COMPONENT;

  COMPONENT nfp_sub_double
    PORT( nfp_in1                         :   IN    std_logic_vector(63 DOWNTO 0);  -- double
          nfp_in2                         :   IN    std_logic_vector(63 DOWNTO 0);  -- double
          nfp_out                         :   OUT   std_logic_vector(63 DOWNTO 0)  -- double
          );
  END COMPONENT;

  -- Component Configuration Statements
  FOR ALL : nfp_mul_double
    USE ENTITY work.nfp_mul_double(rtl);

  FOR ALL : nfp_sub_double
    USE ENTITY work.nfp_sub_double(rtl);

  -- Signals
  SIGNAL kconst                           : std_logic_vector(63 DOWNTO 0);  -- ufix64
  SIGNAL Out_1                            : std_logic_vector(63 DOWNTO 0);  -- ufix64
  SIGNAL out0                             : std_logic_vector(63 DOWNTO 0);  -- ufix64
  SIGNAL kconst_1                         : std_logic_vector(63 DOWNTO 0);  -- ufix64
  SIGNAL out0_1                           : std_logic_vector(63 DOWNTO 0);  -- ufix64

BEGIN
  u_nfp_mul_comp : nfp_mul_double
    PORT MAP( nfp_in1 => w,  -- double
              nfp_in2 => w,  -- double
              nfp_out => Out_1  -- double
              );

  u_nfp_mul_comp_1 : nfp_mul_double
    PORT MAP( nfp_in1 => kconst,  -- double
              nfp_in2 => Out_1,  -- double
              nfp_out => out0  -- double
              );

  u_nfp_mul_comp_2 : nfp_mul_double
    PORT MAP( nfp_in1 => kconst_1,  -- double
              nfp_in2 => w,  -- double
              nfp_out => out0_1  -- double
              );

  u_nfp_sub_comp : nfp_sub_double
    PORT MAP( nfp_in1 => out0,  -- double
              nfp_in2 => out0_1,  -- double
              nfp_out => dw  -- double
              );

  kconst <= X"bfb626d4801f7510";

  kconst_1 <= X"4043f374bc6a7efa";

END rtl;
