.PHONY: clean All

All:
	@echo ----------Building project:[ t6c2e1 - Debug ]----------
	@cd "t6c2e1" && "$(MAKE)" -f "t6c2e1.mk"
clean:
	@echo ----------Cleaning project:[ t6c2e1 - Debug ]----------
	@cd "t6c2e1" && "$(MAKE)" -f "t6c2e1.mk" clean
