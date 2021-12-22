# Change Log

## v0.1.0a0:

### Added/modified
- `d_features`:
	* No need to specify `val_type` nor `evaluate` (#12)
	* New keyword: `restrict` (#7)
	* New type: `dependent` (#12)
- logger:
	* New logging system (#10)

### Fixed
- bugs:
	* `compute_avg` and multithreading (#6)
	* LLVM-MCA does not work with Intel ASM syntax