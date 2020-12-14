load_package flow
set top_level FPGA_SMC
set src_dir "[pwd]"
set prj_dir "q2dir"
file mkdir ../$prj_dir
cd ../$prj_dir
project_new $top_level -revision $top_level -overwrite
set_global_assignment -name FAMILY "Stratix IV"
set_global_assignment -name DEVICE EP4SGX230KF40C2
set_global_assignment -name TOP_LEVEL_ENTITY $top_level
set_global_assignment -name VHDL_FILE "$src_dir/nfp_sub_double.vhd"
set_global_assignment -name VHDL_FILE "$src_dir/nfp_mul_double.vhd"
set_global_assignment -name VHDL_FILE "$src_dir/Model.vhd"
set_global_assignment -name VHDL_FILE "$src_dir/nfp_add_double.vhd"
set_global_assignment -name VHDL_FILE "$src_dir/nfp_abs_double.vhd"
set_global_assignment -name VHDL_FILE "$src_dir/nfp_relop_double.vhd"
set_global_assignment -name VHDL_FILE "$src_dir/nfp_relop_double_block.vhd"
set_global_assignment -name VHDL_FILE "$src_dir/nfp_signum_double.vhd"
set_global_assignment -name VHDL_FILE "$src_dir/nfp_sqrt_double.vhd"
set_global_assignment -name VHDL_FILE "$src_dir/nfp_add2_double.vhd"
set_global_assignment -name VHDL_FILE "$src_dir/FPGA_SMC.vhd"
execute_flow -compile
project_close
