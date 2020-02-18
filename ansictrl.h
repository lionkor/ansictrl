#ifndef ANSICTRL_H
#define ANSICTRL_H

#include <cstdint>
#include <cstdio>

namespace ansi {
using u32                        = std::uint32_t;
static constexpr const char* ESC = "\033[";
}

namespace ansi::graphics::color::fg {
static constexpr const char* BLACK   = "30";
static constexpr const char* RED     = "31";
static constexpr const char* GREEN   = "32";
static constexpr const char* YELLOW  = "33";
static constexpr const char* BLUE    = "34";
static constexpr const char* MAGENTA = "35";
static constexpr const char* CYAN    = "36";
static constexpr const char* WHITE   = "37";
}

namespace ansi::graphics::color::bg {
static constexpr const char* BLACK   = "40";
static constexpr const char* RED     = "41";
static constexpr const char* GREEN   = "42";
static constexpr const char* YELLOW  = "43";
static constexpr const char* BLUE    = "44";
static constexpr const char* MAGENTA = "45";
static constexpr const char* CYAN    = "46";
static constexpr const char* WHITE   = "47";
}

namespace ansi::graphics::attribute {
static constexpr const char* NOATTRIB   = "0";
static constexpr const char* BOLD       = "1";
static constexpr const char* UNDERSCORE = "4";
static constexpr const char* BLINK      = "5";
static constexpr const char* REVERSE    = "7";
static constexpr const char* CONCEALED  = "8";
}

namespace ansi::term::internal {
static inline void esc() {
    printf("%s", ansi::ESC);
}
}

namespace ansi::term {
static inline void set_cursor_pos(u32 line, u32 column) {
    internal::esc();
    printf("%u;%uH", line, column);
}

enum class dir
{
    Up,
    Down,
    Forward,
    Backward
};

static inline void move_cursor(dir d, u32 amount) {
    internal::esc();
    char direction = 0;
    switch (d) {
    case dir::Up:
        direction = 'A';
        break;
    case dir::Down:
        direction = 'B';
        break;
    case dir::Forward:
        direction = 'C';
        break;
    case dir::Backward:
        direction = 'D';
        break;
    }
    printf("%u%c", amount, direction);
}

static inline void clear_screen() {
    internal::esc();
    printf("2J");
}

static inline void save_cursor_pos() {
    internal::esc();
    printf("s");
}

static inline void restore_cursor_pos() {
    internal::esc();
    printf("u");
}

static inline void clear_line() {
    internal::esc();
    printf("K");
}

enum class color
{
    Black,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White,
    DontChange
};

static inline void set_color(color foreground, color background = color::DontChange) {
    internal::esc();
    const char* fg;
    const char* bg;

    switch (foreground) {
    case color::Black:
        fg = ansi::graphics::color::fg::BLACK;
        break;
    case color::Red:
        fg = ansi::graphics::color::fg::RED;
        break;
    case color::Green:
        fg = ansi::graphics::color::fg::GREEN;
        break;
    case color::Yellow:
        fg = ansi::graphics::color::fg::YELLOW;
        break;
    case color::Blue:
        fg = ansi::graphics::color::fg::BLUE;
        break;
    case color::Magenta:
        fg = ansi::graphics::color::fg::MAGENTA;
        break;
    case color::Cyan:
        fg = ansi::graphics::color::fg::CYAN;
        break;
    case color::White:
        fg = ansi::graphics::color::fg::WHITE;
        break;
    case color::DontChange:
        fg = nullptr;
        break;
    }

    switch (background) {
    case color::Black:
        bg = ansi::graphics::color::bg::BLACK;
        break;
    case color::Red:
        bg = ansi::graphics::color::bg::RED;
        break;
    case color::Green:
        bg = ansi::graphics::color::bg::GREEN;
        break;
    case color::Yellow:
        bg = ansi::graphics::color::bg::YELLOW;
        break;
    case color::Blue:
        bg = ansi::graphics::color::bg::BLUE;
        break;
    case color::Magenta:
        bg = ansi::graphics::color::bg::MAGENTA;
        break;
    case color::Cyan:
        bg = ansi::graphics::color::bg::CYAN;
        break;
    case color::White:
        bg = ansi::graphics::color::bg::WHITE;
        break;
    case color::DontChange:
        bg = nullptr;
        break;
    }

    if (fg) {
        if (bg)
            printf("%s;%sm", fg, bg);
        else
            printf("%sm", fg);
    } else {
        if (bg)
            printf("%sm", bg);
        else
            ; // both are DontChange
    }
}

static inline void clear_attributes() {
    internal::esc();
    printf("%sm", ansi::graphics::attribute::NOATTRIB);
}

static inline void bold_on() {
    internal::esc();
    printf("%sm", ansi::graphics::attribute::BOLD);
}

static inline void underscore_on() {
    internal::esc();
    printf("%sm", ansi::graphics::attribute::UNDERSCORE);
}

static inline void blink_on() {
    internal::esc();
    printf("%sm", ansi::graphics::attribute::BLINK);
}

static inline void reverse_on() {
    internal::esc();
    printf("%sm", ansi::graphics::attribute::REVERSE);
}

static inline void concealed_on() {
    internal::esc();
    printf("%sm", ansi::graphics::attribute::CONCEALED);
}

static inline void enable_line_wrapping() {
    internal::esc();
    printf("=7h");
}

static inline void disable_line_wrapping() {
    internal::esc();
    printf("=7l");
}
}

#endif // ANSICTRL_H
