# Agents

## Commands

**Build:**
```
make build
```

**Run:**
```
make run
```

**Test:**
```
make test
```

**Clean:**
```
make clean
```

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for dev container setup, make commands, TDD workflow, and how to work with ADRs.

See [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md) for community standards.

## Architecture decisions

Our architecture decisions live in `docs/adr/`. Read them before changing the build system, tooling, or test setup.

## Code style

- Private member variables start with an underscore followed by a lowercase letter (`_x`, `_count`). Never use an underscore followed by an uppercase letter (`_X`): those names are reserved by the C++ standard.

## Rules

- Never go against an accepted ADR. To change a decision, write a new ADR with status `Proposed` and ask the user.
- Never set an ADR status to `Accepted`.
