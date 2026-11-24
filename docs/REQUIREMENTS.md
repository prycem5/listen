# Listen: Requirements

A local-first mobile music player with a smart mix feature that learns from the user's listening habits. Built with React Native (TypeScript).

**This file is the source of truth for scope.** If a feature isn't listed here, it isn't part of the current milestone. New ideas go in the [Parking Lot](#parking-lot), not into code.

---

## 1. Project Rules

1. **Scope changes happen in this file first.** Edit the requirement, add a line to the [Change Log](#change-log), then write code.
2. **One milestone at a time.** Don't start the next one until the current one meets its Definition of Done.
3. **Logic before looks.** Build each feature with a plain, functional UI first. The styling pass comes after the logic works, using design docs (see [Design](#7-design)).
4. **I write and can explain** the data layer, playback wrapper, screen structure, state logic, and Smart Mix scoring. AI assistance is for the visual styling pass and for review.
5. **Every milestone ends with something usable:** a build that runs on the emulator, a git tag, and updated checkboxes in this file.
6. **Cut scope before cutting quality.** If time runs short, drop a "Should" item, not tests or the README.

---

## 2. Decisions

### Decided

| Area | Decision |
|---|---|
| Framework | React Native with Expo, TypeScript |
| Build target (first) | Android, using the Android emulator on Linux. iOS is deferred. |
| Build type | Development build (not Expo Go), because background playback needs native code |
| Database | SQLite (via `expo-sqlite`), accessed with plain SQL |
| Tag editing | **Database only.** Edits update the app's database and never write to audio files. |
| Song import | Copy files into an app-managed folder |
| Recommender | Weighted heuristic, written in TypeScript. No C++/native modules. |
| Privacy | All data stays on the device. No accounts, no network features. |
| Theme | Dark mode only |

### Open (decide during the milestone shown)

| Question | Candidates | Decide in |
|---|---|---|
| Playback library | `react-native-track-player`, `expo-audio` | v1 spike |
| Tag *reading* library (for import) | `jsmediatags`, `expo-music-info-2`, others | v1 spike |
| Supported audio formats | Defined by what the playback and tag libraries handle on Android | v1 spike |
| Skip threshold for Smart Mix | Default 30 s, configurable | v4 |
| Album identity rules | Album = album artist + album title | v3 |
| UI list component | `FlatList` vs a faster list library | v2 |

---

## 3. Milestones

### v1: Import and Play
*Goal: get music into the app and hear it, even in the background.*

- [ ] **Spike first:** import one MP3 and play it from a development build on the emulator
- [ ] Local import (IMP-1 to IMP-5)
- [ ] Playback (PLAY-1 to PLAY-8)
- [ ] Plain song list screen, sorted alphabetically

**Done when:** I can import several songs, play, pause, skip, seek, and queue them, and playback continues with the app in the background and the screen locked.

### v2: Navigation and Search
*Goal: find anything in the library quickly.*

- [ ] Album, artist, and song menus (NAV-1 to NAV-4)
- [ ] Search (SRCH-1 to SRCH-4)
- [ ] Tapping album art on the player opens that album (PLAY-9)

**Done when:** every song can be reached by browsing albums, artists, or search, and search results navigate to the right screen.

### v3: Metadata Editing
*Goal: fix tags in the app.*

- [ ] Single-song editing (TAG-1 to TAG-3)
- [ ] Album-level editing with warning (TAG-4 to TAG-6)
- [ ] Album art editing (TAG-7)

**Done when:** I can correct a messy imported album in the app and see the changes everywhere (lists, player, search).

### v4: Smart Mix
*Goal: the differentiator.*

- [ ] Consent and privacy screen (MIX-1 to MIX-3)
- [ ] Listening log (MIX-4)
- [ ] Scoring and mix generation (MIX-5 to MIX-9)
- [ ] Save mix as a playlist (MIX-10, LIB-1)

**Done when:** after listening for a while, a mix can be created from the main menu, and unit tests show the scoring responds to skips and listening history as designed.

### Stretch (only after v1 to v4 are done and polished)
1. **Smart Import:** make importing music from other sources easier (handle odd folders and file names).
2. **Auto metadata:** fill in missing tags automatically.
3. **User themes:** beyond dark mode.

---

## 4. Functional Requirements

**Priority:** **Must** = required for its milestone. **Should** = include if time allows.

### Import (v1)

| ID | Requirement | Priority |
|---|---|---|
| IMP-1 | User can select one or more audio files with the system file picker | Must |
| IMP-2 | Selected files are copied into an app-managed folder | Must |
| IMP-3 | Tags (title, artist, album artist, album, year, track no., disc no., genre, embedded art) are read at import and stored in the database | Must |
| IMP-4 | A bad file doesn't abort the batch. Failures are listed at the end. | Must |
| IMP-5 | Exact duplicates are detected and skipped, and the user is told | Should |
| IMP-6 | User can remove a song from the library, which deletes its copy | Must |

### Playback (v1, v2)

| ID | Requirement | Priority |
|---|---|---|
| PLAY-1 | Play and pause | Must |
| PLAY-2 | Skip forward and backward | Must |
| PLAY-3 | Seek using a progress bar showing elapsed and total time | Must |
| PLAY-4 | Player screen shows album art in the center, with album artist and song title | Must |
| PLAY-5 | Queue: add songs, view, reorder, remove | Must |
| PLAY-6 | Shuffle and repeat (off, all, one) | Must |
| PLAY-7 | Playback continues in the background, with lock-screen / notification controls | Must |
| PLAY-8 | Playback pauses when headphones are unplugged or during a call | Should |
| PLAY-9 | Tapping the album art opens that album's screen | Must |

### Navigation (v2)

| ID | Requirement | Priority |
|---|---|---|
| NAV-1 | Menus for Albums, Artists, and Songs | Must |
| NAV-2 | Albums and artists are sorted alphanumerically | Must |
| NAV-3 | Tapping an album shows its tracks in track order (disc, then track no.) | Must |
| NAV-4 | Tapping an artist shows their albums and songs | Must |

### Search (v2)

| ID | Requirement | Priority |
|---|---|---|
| SRCH-1 | Search bar at the top of the screen | Must |
| SRCH-2 | A single query matches song names, album names, and artist names (case-insensitive) | Must |
| SRCH-3 | Results are grouped into Songs, Albums, and Artists | Must |
| SRCH-4 | Tapping a result opens the matching screen (song plays, album and artist open their menus) | Must |

### Metadata Editing (v3)

| ID | Requirement | Priority |
|---|---|---|
| TAG-1 | Edit a single song's release year, artist, album artist, album, track no., and disc no. | Must |
| TAG-2 | Edits are saved to the database only. Audio files are never modified. | Must |
| TAG-3 | Edits show up immediately in all lists, the player, and search | Must |
| TAG-4 | Edit album-level values (album title, album artist, year) for all songs in an album at once | Must |
| TAG-5 | Before applying an album edit, show a warning stating how many songs will change, with Confirm and Cancel | Must |
| TAG-6 | Renaming an album updates the album record, so albums don't split or merge by accident | Must |
| TAG-7 | Change album art for a single song or a whole album (copy the chosen image into app storage) | Must |

### Playlists (v4)

| ID | Requirement | Priority |
|---|---|---|
| LIB-1 | Create, rename, and delete playlists; add and remove songs | Must |

### Smart Mix (v4)

| ID | Requirement | Priority |
|---|---|---|
| MIX-1 | On first use, show a consent screen explaining what is logged (plays, skips, listening time) and that all data stays on the device | Must |
| MIX-2 | Smart Mix only logs data after the user agrees | Must |
| MIX-3 | Settings let the user turn logging off and delete all listening data | Must |
| MIX-4 | Log events: song started, song ended or skipped, seconds listened, timestamp | Must |
| MIX-5 | Score candidate songs using these signals: **user input** (songs skipped before X seconds count negatively), **artist** (song artist and album artist), **genre** (if tagged), **album**, and **song profile** (BPM only if present in the tags) | Must |
| MIX-6 | Weights live in one configuration object with defaults, not scattered in code | Must |
| MIX-7 | Missing data (no genre, no BPM) is treated as neutral, never as a penalty | Must |
| MIX-8 | Cold start: with little history, fall back to tag similarity plus some randomness | Must |
| MIX-9 | A mix can be created from the main menu. It samples from the top-scoring songs (not strictly the top N) and avoids recently played songs. | Must |
| MIX-10 | A mix can be saved as a playlist | Must |

**Scoring sketch (to refine in v4):**

```
score = w_artist * artist_affinity
      + w_genre  * genre_affinity
      + w_album  * album_affinity
      + w_bpm    * bpm_closeness        (only if both songs have BPM)
      + w_skip   * skip_signal          (negative for recent early skips)
      - w_recent * recently_played
```

Every feature is normalized to 0-1 before weighting.

---

## 5. Data Model (initial sketch)

```
tracks(id, album_id, title, artist, track_no, disc_no, year, genre, bpm,
       duration, file_path, art_path, added_at)
albums(id, title, album_artist, year, art_path)        -- identity: album_artist + title
artists(id, name)
playlists(id, name, created_at)
playlist_tracks(playlist_id, track_id, position)
play_events(id, track_id, started_at, seconds_listened, completed, source)
settings(key, value)                                    -- consent flag, weights, skip threshold
```

Changing a table is allowed, but note it in the Change Log.

---

## 6. Non-Functional Requirements

- **Local-first:** all features work offline, and no network permission is needed for v1 to v4.
- **Privacy:** no listening data leaves the device, and users can delete it.
- **Performance target:** a library of about 2,000 songs scrolls smoothly (use a virtualized list). Measure on the emulator in v2.
- **Reliability:** an import never loses or corrupts the original file, and a failed import leaves no half-copied files.
- **Testing:** unit tests for Smart Mix scoring, the database queries, and album identity and edit logic.
- **Documentation:** a README with screenshots, a short demo GIF, setup steps, and a section on design decisions.

---

## 7. Design

- Dark mode only for now.
- Build functional screens first. Then write design docs in `docs/design/` (colors, type scale, spacing, component examples, reference images) and do a styling pass.
- Every screen needs an empty state (no songs yet) and an error state.

---

## Parking Lot

Ideas that are **not** in scope until v1 to v4 are done.

- iOS build and testing (needs a paid developer account, to be checked)
- Writing tags into audio files
- C++ or other native modules
- Cloud sync, accounts, social features
- Lyrics, equalizer, sleep timer, car mode
- Import by folder or by watching a device folder

---

## Change Log

| Date | Change | Reason |
|---|---|---|
| (initial) | First version of requirements | Scope agreed before development started |
