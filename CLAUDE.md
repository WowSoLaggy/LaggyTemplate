# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Important Notes

Always respect this section!

This is not comprehensive documentation — it's an index of what lives where and the conventions to follow. For algorithm details, read the source. Describe *where* a thing is and *why* it's shaped that way, not the step-by-step of how it works. Don't embed constant values or tunable lists — point at the file that owns them.

Don't add long descriptions here - it shall be as short and as concise as possible. If you need to explain a concept, it shall readable from the code itself.

After making any change that affects the architecture, file layout, build setup, or conventions described above, **update `CLAUDE.md` in the same turn**. If a change might warrant an update but you're not sure, **explicitly notify the user** ("CLAUDE.md may need updating: X is no longer accurate") rather than silently leaving it stale.

Never run app without me explicitly asking for it.
Never modify DirectXTK repo!

## Sibling-repo dependencies

The solution references sibling projects by relative path — they must exist at the expected locations or the build will fail:

- `<repo_root>\LaggySdk\LaggySdk\LaggySdk.vcxproj` — utility library (event system, contracts, math, Win32 wrappers, `EntityId` registry). Headers included as `<LaggySdk/Foo.h>`.
- `<repo_root>\LaggyDx\LaggyDx\LaggyDx.vcxproj` — DirectX 11 engine (`Dx::App`, renderers, GUI tree, resource controller, input). Headers included as `<LaggyDx/Foo.h>`.
- `<repo_root>\DirectXTK\DirectXTK_Desktop_2022_Win10.vcxproj` — Microsoft's DirectXTK, consumed transitively via `LaggyDx`.

Both `LaggySdk` and `LaggyDx` have their own `CLAUDE.md` at `<repo_root>\LaggySdk\CLAUDE.md` and `<repo_root>\LaggyDx\CLAUDE.md`. Read those when working on engine internals.

Include paths come from `<app_name>/Laggy.props`: `$(SolutionDir)..\DirectXTK\Inc;$(SolutionDir)..\LaggySdk;$(SolutionDir)..\LaggyDx;`.

## Building

Build the solution with MSBuild (it pulls in the sibling projects automatically). The output is `<app_name>\bin\<app_name>.exe`. E.g.:

```powershell
& "C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\amd64\MSBuild.exe" `
  <app_name>\<app_name>.sln /p:Configuration=Release /p:Platform=x64 /m
```

## Version control

Commit to the **current branch**. Do not create or switch branches for commits unless the user explicitly asks. This overrides the default "branch off the default branch before committing" behavior.

## Conventions worth matching

These mirror the sibling libraries — see `..\LaggySdk\CLAUDE.md` for the canonical list.

- Parameter naming: `i_` for in, `o_` for out, `a_` for accumulator/in-out, `d_` for data members, `s_` for statics.
- Two-space indentation, Allman braces, `#pragma once` on every header.
- Don't add `#include`s for the C++ standard library — they come transitively via `<LaggySdk/Common.h>`. If one is genuinely missing, add it *there*, not locally.
- Const-correctness: add `const` wherever possible, especially on input parameters and non-mutated locals.
- Use the `CONTRACT_ASSERT` / `CONTRACT_EXPECT` / `CONTRACT_ENSURE` / `CONTRACT_THROW` / `SAFE_DEREF` macros from `<LaggySdk/Contracts.h>` instead of `assert`, raw `throw`, or ad-hoc null checks. `Game.cpp` uses `SAFE_DEREF` pervasively for `shared_ptr` member access — match that.
- For engine subsystems exposed as `IFoo`, include the `IFoo` header and call `IFoo::create(...)`. Don't `#include` the concrete implementation from `LaggyDx`.
- Clean functions: Keep abstraction level - don't add low-level logic to the same function that owns high-level orchestration; Extract independent parts into their own functions. Avoid "god functions" that do everything; break them into smaller, readable pieces.
- Comments must be one-liners: concise and to the point. Never write multiline block comments, even for doc comments above a declaration — collapse them to a single line. This overrides any tendency to match a surrounding multiline comment style.

## How to write code

Always write / modify code according to this section!
First, work on entities (classes / structs) and interfaces. Don't dive into implementation until confirmed by user.
Never overengineer - do the simplest solution with obvious connections.
Write correct, readable, and maintainable code. Prefer the standard library and RAII; avoid unnecessary complexity and undefined behavior.

## Architecture

This is a thin **`Dx::App` subclass** — almost all the heavy lifting lives in `LaggyDx`. The whole project has no namespace (the app's own types live in the global namespace; engine types are in `Dx::` and `Sdk::`).

### Entry point and `Game` singleton

- General:
  - `main.cpp` is a one line entry point. `Game` (`Game.{h,cpp}`) derives from `Dx::App` and is a singleton. Subsystems reach back via `Game::get().getX()`.
  - `stdafx.{h,cpp}` is the precompiled header.
  - `Fwd.h` forward-declares the app's own types and includes `<LaggySdk/SdkFwd.h>`. Include `Fwd.h` instead of concrete headers when only references/pointers are needed.
- Core:
  - `Game.{h,cpp}` owns the subsystems and drives the frame loop.
  - `Game_input.cpp` redirects input events to `InputManager`.
  - `InputManager.{h,cpp}` handles all input.
  - `CameraController.{h,cpp}` drives the 3D camera from input.
  - `SimClock.{h,cpp}` tracks global vs. simulation time.
  - `GuiController.{h,cpp}` owns the GUI tree; `Game::onNewGame` calls `createGameUi()` on it.
  - `Background.{h,cpp}` renders the background sprite; drawn in `Game::render`.
  - `DrawLayers.h` defines sprite draw-order constants.
