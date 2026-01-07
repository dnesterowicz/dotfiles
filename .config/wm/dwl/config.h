#define TAGCOUNT (4)
#define COLOR(hex)                                                             \
  {((hex >> 24) & 0xFF) / 255.0f, ((hex >> 16) & 0xFF) / 255.0f,               \
   ((hex >> 8) & 0xFF) / 255.0f, (hex & 0xFF) / 255.0f}

static int log_level = WLR_ERROR;

static const Rule rules[] = {
    /* app_id  title  tags_mask  isfloating  isterm  noswallow  monitor */
    {"foot", NULL, 1, 0, 1, 0, -1},
    {"librewolf", NULL, 2, 0, 0, 0, -1},
};

static const Layout layouts[] = {
    {"[]=", tile},
    {"><>", NULL}, /* no layout function means floating behavior */
};

/* appearance */
static const float rootcolor[] = COLOR(0x222222ff);
static const float bordercolor[] = COLOR(0x444444ff);
static const float focuscolor[] = COLOR(0x005577ff);
static const float urgentcolor[] = COLOR(0xff0000ff);
static const float fullscreen_bg[] = {0.0f, 0.0f, 0.0f, 1.0f};
static const unsigned int borderpx = 3;
static int gaps = 1;
static const unsigned int gappx = 10;
static const int smartgaps = 1;
static const int sloppyfocus = 1; /* focus follows mouse */
static const int bypass_surface_visibility = 0;
static int enableautoswallow = 1;
static float swallowborder = 1.0f;

/* monitors */
static const MonitorRule monrules[] = {
    /* name  mfact  nmaster  scale  layout rotate/reflect x y */
    {NULL, 0.55f, 1, 1, &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL, -1, -1},
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
    /* can specify fields: rules, model, layout, variant, options */
    // .layout = "pl",
    .options = NULL,
};
static const int repeat_rate = 25;
static const int repeat_delay = 600;

/* trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 0;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;
static const enum libinput_config_scroll_method scroll_method =
    LIBINPUT_CONFIG_SCROLL_2FG;
static const enum libinput_config_click_method click_method =
    LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;
static const enum libinput_config_accel_profile accel_profile =
    LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
static const double accel_speed = 0.0;
static const enum libinput_config_tap_button_map button_map =
    LIBINPUT_CONFIG_TAP_MAP_LRM;
static const int cursor_timeout = 5;

#define MODKEY WLR_MODIFIER_ALT
#define TAGKEYS(KEY, SKEY, TAG)                                                \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
  {MODKEY | WLR_MODIFIER_CTRL, KEY, toggleview, {.ui = 1 << TAG}},         \
  {MODKEY | WLR_MODIFIER_SHIFT, SKEY, tag, {.ui = 1 << TAG}}, \
  {MODKEY | WLR_MODIFIER_CTRL | WLR_MODIFIER_SHIFT, SKEY, toggletag, { .ui = 1 << TAG }} \

#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

#define CHVT(n)                                                                \
  {                                                                            \
    WLR_MODIFIER_CTRL | WLR_MODIFIER_ALT, XKB_KEY_XF86Switch_VT_##n, chvt, {   \
      .ui = (n)                                                                \
    }                                                                          \
  }

static const Key keys[] = {
    /* modifier            key                 function        argument */
    TAGKEYS(XKB_KEY_1, XKB_KEY_exclam, 0),
    TAGKEYS(XKB_KEY_2, XKB_KEY_at, 1),
    TAGKEYS(XKB_KEY_3, XKB_KEY_numbersign, 2),
    TAGKEYS(XKB_KEY_4, XKB_KEY_dollar, 3),
    CHVT(1),
    CHVT(2),
    CHVT(3),
    CHVT(4),

	{ MODKEY,                    XKB_KEY_d,       shiftview,      {.i = -1 } },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_D,       shifttag,       {.i = -1 } },
	{ MODKEY,                    XKB_KEY_f,      shiftview,      {.i = +1 } },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_F,      shifttag,       {.i = +1 } },

    {MODKEY, XKB_KEY_l, focusstack, {.i = +1}},
    {MODKEY, XKB_KEY_h, focusstack, {.i = -1}},
    {MODKEY, XKB_KEY_u, togglefullscreen, {0}},
    {MODKEY | WLR_MODIFIER_SHIFT, XKB_KEY_space, togglefloating, {0}},
    {MODKEY | WLR_MODIFIER_SHIFT, XKB_KEY_B, togglebar, {0}},
    {MODKEY | WLR_MODIFIER_SHIFT, XKB_KEY_C, killclient, {0}},
    {MODKEY | WLR_MODIFIER_SHIFT, XKB_KEY_Q, quit, {0}},

    // audio & display control
    {0, XKB_KEY_XF86AudioMute, spawn, SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle")},
    {0, XKB_KEY_XF86AudioLowerVolume, spawn, SHCMD("wpctl set-volume -l 1.0 @DEFAULT_AUDIO_SINK@ 5%-")},
    {0, XKB_KEY_XF86AudioRaiseVolume, spawn, SHCMD("wpctl set-volume -l 1.0 @DEFAULT_AUDIO_SINK@ 5%+")},
    {0, XKB_KEY_XF86AudioMicMute, spawn, SHCMD("wpctl set-mute @DEFAULT_AUDIO_SOURCE@ toggle")},
    {MODKEY, XKB_KEY_Left, spawn, SHCMD("mpc prev")},
    {MODKEY, XKB_KEY_Right, spawn, SHCMD("mpc next")},
    {MODKEY, XKB_KEY_Down, spawn, SHCMD("mpc toggle")},
    {0, XKB_KEY_XF86MonBrightnessDown, spawn, SHCMD("backlight_control -5")},
    {0, XKB_KEY_XF86MonBrightnessUp, spawn, SHCMD("backlight_control +5")},
    {0, XKB_KEY_Print, spawn, SHCMD("screenshot")},

    // scratchpad
    {MODKEY, XKB_KEY_z, togglescratchpad, {0}},
    {MODKEY | WLR_MODIFIER_SHIFT, XKB_KEY_Z, addscratchpad, {0}},
    {MODKEY | WLR_MODIFIER_CTRL, XKB_KEY_z, removescratchpad, {0}},

    // utilities
    {MODKEY, XKB_KEY_r, spawn, SHCMD("eval $RUNNER $MENU_OPTS")},
    {MODKEY, XKB_KEY_Insert, spawn, SHCMD("bookmark")},
    {MODKEY, XKB_KEY_p, spawn, SHCMD("passmenu-otp")},
    {MODKEY, XKB_KEY_x, spawn, SHCMD("shutdownprompt")},
    {MODKEY | WLR_MODIFIER_SHIFT, XKB_KEY_L, spawn, SHCMD("waylock")},
    {MODKEY | WLR_MODIFIER_SHIFT, XKB_KEY_P, spawn, SHCMD("cliptofile")},

    //  programs
    {MODKEY, XKB_KEY_w, spawn, SHCMD("$BROWSER")},
    {MODKEY, XKB_KEY_Return, spawn, SHCMD("$TERMINAL")},
    {MODKEY, XKB_KEY_n, spawn, SHCMD("$TERMINAL newsboat")},
    {MODKEY, XKB_KEY_m, spawn, SHCMD("$TERMINAL ncmpcpp")},
};

static const Button buttons[] = {
    {MODKEY, BTN_LEFT, moveresize, {.ui = CurMove}},
    {MODKEY, BTN_RIGHT, moveresize, {.ui = CurResize}},
};
