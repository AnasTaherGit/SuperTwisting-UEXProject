-- -------------------------------------------------------------
-- 
-- File Name: C:\Users\cawoo\My Folders\Electronique\Projet d'expertise\FPGA_SMC_Project\Tested_Controller_2\hdlsrc\FPGA_SMC\Model.vhd
-- Created: 2020-12-14 15:19:47
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
  PORT( w                                 :   IN    std_logic_vector(31 DOWNTO 0);  -- single
        dw                                :   OUT   std_logic_vector(31 DOWNTO 0)  -- single
        );
END Model;


ARCHITECTURE rtl OF Model IS

  ATTRIBUTE multstyle : string;

  -- Component Declarations
  COMPONENT nfp_mul_single
    PORT( nfp_in1                         :   IN    std_logic_vector(31 DOWNTO 0);  -- single
          nfp_in2                         :   IN    std_logic_vector(31 DOWNTO 0);  -- single
          nfp_out                         :   OUT   std_logic_vector(31 DOWNTO 0)  -- single
          );
  END COMPONENT;

  COMPONENT nfp_sub_single
    PORT( nfp_in1                         :   IN    std_logic_vector(31 DOWNTO 0);  -- single
          nfp_in2                         :   IN    std_logic_vector(31 DOWNTO 0);  -- single
          nfp_out                         :   OUT   std_logic_vector(31 DOWNTO 0)  -- single
          );
  END COMPONENT;

  -- Component Configuration Statements
  FOR ALL : nfp_mul_single
    USE ENTITY work.nfp_mul_single(rtl);

  FOR ALL : nfp_sub_single
    USE ENTITY work.nfp_sub_single(rtl);

  -- Signals
  SIGNAL kconst                           : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL Out_1                            : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL out0                             : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL kconst_1                         : std_logic_vector(31 DOWNTO 0);  -- ufix32
  SIGNAL out0_1                           : std_logic_vector(31 DOWNTO 0);  -- ufix32

BEGIN
  u_nfp_mul_comp : nfp_mul_single
    PORT MAP( nfp_in1 => w,  -- single
              nfp_in2 => w,  -- single
              nfp_out => Out_1  -- single
              );

  u_nfp_mul_comp_1 : nfp_mul_single
    PORT MAP( nfp_in1 => kconst,  -- single
              nfp_in2 => Out_1,  -- single
              nfp_out => out0  -- single
              );

  u_nfp_mul_comp_2 : nfp_mul_single
    PORT MAP( nfp_in1 => kconst_1,  -- single
              nfp_in2 => w,  -- single
              nfp_out => out0_1  -- single
              );

  u_nfp_sub_comp : nfp_sub_single
    PORT MAP( nfp_in1 => out0,  -- single
              nfp_in2 => out0_1,  -- single
              nfp_out => dw  -- single
              );

  kconst <= X"bdb136a4";

  kconst_1 <= X"421f9ba6";

END rtl;

