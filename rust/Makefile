all: build
	$(MAKE) check

build:
	cargo build

clean:
	cargo clean

check:
	cargo run
doc:
	cargo doc
	xdg-open target/doc/rust_basics/index.html
