How To add translations to Cobot TP
=====================================

- Coordinate over the mailing list to avoid duplicate work.

- Add your language to the `set(languages ...` line in `CMakeLists.txt`. Don't
  qualify it with a country unless it is reasonable to expect country-specific
  variants. Skip this step if updating an existing translation.

- Configure a Cobot TP build directory with CMake.

- Run `cmake --build . --target ts_<lang>`.

- Start Qt Linguist and translate the strings.

- Create a commit:
  - Discard the modifications to any `.ts` files except yours
  - Create a commit with your file
  - If needed, amend the commit with the modified `CMakeLists.txt` file

- .qm files are generated as part of the regular build.

_Note:_ QmlDesigner contains code from the Gradient Editor of Qt Designer. If an
official translation of Qt for your language exists, you can re-use the
translation of those messages by merging Cobot TP's and Qt Designer's
translation using `lconvert`:

    lconvert cobottp_<LANG>.ts $QTDIR/translations/designer_<LANG>.ts > temp.ts

Move the temporary file back to `cobottp_<LANG>.ts`, complete the Gradient
Editor's translations and update the file, passing the additional option
`-noobsolete` to `lupdate` (by temporarily modifying
`<InoCobotTP>/cmake/CobotTPTranslations.cmake`). This will remove the now
redundant messages originating from Qt Designer.
