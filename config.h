/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 2;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:pixelsize=11:antialias=true:autohint=true" };
static const char dmenufont[]       = "monospace:pixelsize=11";
static const unsigned int baralpha = 0xcc;
static const unsigned int borderalpha = OPAQUE;
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      		instance    		title       		tags mask	iscentered	isfloating	monitor */
	{"qutebrowser",  	"qutebrowser",		NULL,			1,		0,             	0,           	-1 },
	{"firefox",  		"Navigator",		NULL,			1,		0,             	0,           	-1 },
	{"Brave-browser",	"brave-browser",	NULL,			1,		0,             	0,           	-1 },
	{"Alacritty",		"Alacritty",		"pulsemixer",		0,		1,	       	1,		-1 },
	{"Alacritty",		"Alacritty",		"nmtui",		0,		1,	       	1,	    	-1 },
	{"Blueman-manager",	"blueman-manager",	"Bluetooth Devices",	0,		1,	       	1,	    	-1 },
	{"KeePassXC",		"keepassxc",		"Generate Password",	0,		1,	       	1,	    	-1 },
	{"Element",		"element",		"Element",		1 << 6,		0,		0,	    	-1 },
	{"TelegramDesktop",	"telegram-desktop",	"Telegram",		1 << 7,		0,		0,	    	-1 },
	{"discord",		"discord",		"Discord",		1 << 5,		0,		0,	    	-1 },
};

/* layout(s) */
static const float mfact     = 0.5;  /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int attachbelow = 1;    /* 1 means attach after the currently active window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run_history", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "alacritty", NULL };

static Key keys[] = {
	/* modifier                     key        	function        	argument */
	{ MODKEY,			XK_d,      	spawn,			{.v = dmenucmd } },
	{ MODKEY,			XK_Return, 	spawn,			{.v = termcmd } },
	{ MODKEY,                       XK_b,      	togglebar,		{0} },
	{ MODKEY|ShiftMask,		XK_c,		setcentered,		{0} },
	{ MODKEY,                       XK_j,      	focusstack,     	{.i = +1 } },
	{ MODKEY,                       XK_k,      	focusstack,     	{.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      	incnmaster,     	{.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      	incnmaster,     	{.i = -1 } },
	{ MODKEY,                       XK_h,      	setmfact,       	{.f = -0.05} },
	{ MODKEY,                       XK_l,      	setmfact,       	{.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, 	zoom,           	{0} },
	{ MODKEY,                       XK_Tab,    	view,           	{0} },
	{ MODKEY,			XK_q,      	killclient,     	{0} },
	{ MODKEY,                       XK_t,      	setlayout,      	{.v = &layouts[0]} },
	{ MODKEY,                       XK_y,      	setlayout,      	{.v = &layouts[1]} },
	{ MODKEY,                       XK_u,      	setlayout,      	{.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  	setlayout,      	{0} },
	{ MODKEY|ShiftMask,             XK_space,  	togglefloating, 	{0} },
	{ MODKEY,                       XK_0,      	view,           	{.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      	tag,            	{.ui = ~0 } },
	{ MODKEY,                       XK_comma,  	focusmon,       	{.i = -1 } },
	{ MODKEY,                       XK_period, 	focusmon,       	{.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  	tagmon,         	{.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, 	tagmon,         	{.i = +1 } },
	{ MODKEY,                       XK_F5,  	xrdb,           	{0} },
	TAGKEYS(                        XK_1,                      		0)
	TAGKEYS(                        XK_2,                      		1)
	TAGKEYS(                        XK_3,                      		2)
	TAGKEYS(                        XK_4,                      		3)
	TAGKEYS(                        XK_5,                      		4)
	TAGKEYS(                        XK_6,                      		5)
	TAGKEYS(                        XK_7,                      		6)
	TAGKEYS(                        XK_8,                      		7)
	TAGKEYS(                        XK_9,                      		8)
	{ MODKEY|ControlMask,		XK_F2,      	quit,           	{0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
	/* signum           function */
	//{ "focusstack",     focusstack },
	//{ "setmfact",       setmfact },
	//{ "togglebar",      togglebar },
	//{ "incnmaster",     incnmaster },
	//{ "togglefloating", togglefloating },
	//{ "focusmon",       focusmon },
	//{ "tagmon",         tagmon },
	//{ "zoom",           zoom },
	//{ "view",           view },
	//{ "viewall",        viewall },
	//{ "viewex",         viewex },
	//{ "toggleview",     view },
	//{ "toggleviewex",   toggleviewex },
	//{ "tag",            tag },
	//{ "tagall",         tagall },
	//{ "tagex",          tagex },
	//{ "toggletag",      tag },
	//{ "toggletagex",    toggletagex },
	//{ "killclient",     killclient },
	//{ "quit",           quit },
	//{ "setlayout",      setlayout },
	//{ "setlayoutex",    setlayoutex },
	{ "xrdb",		xrdb },
};

