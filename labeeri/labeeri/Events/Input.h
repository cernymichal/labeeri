#pragma once

namespace labeeri {

/**
 * @brief The action taken on a key.
 */
enum class KeyAction : u8 {
    Release = 0,
    Press = 1,
    Repeat = 2
};

#define LAB_MOD_SHIFT LAB_BIT(0)
#define LAB_MOD_CONTROL LAB_BIT(1)
#define LAB_MOD_ALT LAB_BIT(2)
#define LAB_MOD_SUPER LAB_BIT(3)
#define LAB_MOD_CAPS_LOCK LAB_BIT(4)
#define LAB_MOD_NUM_LOCK LAB_BIT(5)

/**
 * @brief GLFW Keyboard key codes.
 */
enum class KeyboardKey : i32 {
    // The unknown key
    Unknown = -1,

    // Printable keys
    Space = 32,
    Apostrophe = 39,  // '
    Comma = 44,       // ,
    Minus = 45,       // -
    Period = 46,      // .
    Slash = 47,       // /
    Number0 = 48,
    Number1 = 49,
    Number2 = 50,
    Number3 = 51,
    Number4 = 52,
    Number5 = 53,
    Number6 = 54,
    Number7 = 55,
    Number8 = 56,
    Number9 = 57,
    Semicolon = 59,  // ;
    Equal = 61,      // =
    A = 65,
    B = 66,
    C = 67,
    D = 68,
    E = 69,
    F = 70,
    G = 71,
    H = 72,
    I = 73,
    J = 74,
    K = 75,
    L = 76,
    M = 77,
    N = 78,
    O = 79,
    P = 80,
    Q = 81,
    R = 82,
    S = 83,
    T = 84,
    U = 85,
    V = 86,
    W = 87,
    X = 88,
    Y = 89,
    Z = 90,
    LeftBracket = 91,  // [
    Backslash = 92,    // \ 
    RightBracket = 93, // ]
    GraveAccent = 96,  // `
    World1 = 161,      // non-US #1
    World2 = 162,      // non-US #2

    // Function keys
    Escape = 256,
    Enter = 257,
    Tab = 258,
    Backspace = 259,
    Insert = 260,
    Delete = 261,
    Right = 262,
    Left = 263,
    Down = 264,
    Up = 265,
    PageUp = 266,
    PageDown = 267,
    Home = 268,
    End = 269,
    CapsLock = 280,
    ScrollLock = 281,
    NumLock = 282,
    PrintScreen = 283,
    Pause = 284,
    F1 = 290,
    F2 = 291,
    F3 = 292,
    F4 = 293,
    F5 = 294,
    F6 = 295,
    F7 = 296,
    F8 = 297,
    F9 = 298,
    F10 = 299,
    F11 = 300,
    F12 = 301,
    F13 = 302,
    F14 = 303,
    F15 = 304,
    F16 = 305,
    F17 = 306,
    F18 = 307,
    F19 = 308,
    F20 = 309,
    F21 = 310,
    F22 = 311,
    F23 = 312,
    F24 = 313,
    F25 = 314,
    NumPad0 = 320,
    NumPad1 = 321,
    NumPad2 = 322,
    NumPad3 = 323,
    NumPad4 = 324,
    NumPad5 = 325,
    NumPad6 = 326,
    NumPad7 = 327,
    NumPad8 = 328,
    NumPad9 = 329,
    NumPadDecimal = 330,
    NumPadDivide = 331,
    NumPadMultiply = 332,
    NumPadSubtract = 333,
    NumPadAdd = 334,
    NumPadEnter = 335,
    NumPadEqual = 336,
    LeftShift = 340,
    LeftControl = 341,
    LeftAlt = 342,
    LeftSuper = 343,
    RightShift = 344,
    RightControl = 345,
    RightAlt = 346,
    RightSuper = 347,
    Menu = 348
};

/**
 * @brief GLFW Mouse button codes.
 */
enum class MouseButton : u8 {
    Button1 = 0,
    Button2 = 1,
    Button3 = 2,
    Button4 = 3,
    Button5 = 4,
    Button6 = 5,
    Button7 = 6,
    Button8 = 7,
    Left = 0,
    Right = 1,
    Middle = 2
};

}  // namespace labeeri
