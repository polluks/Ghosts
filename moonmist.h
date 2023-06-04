! ----------------------------------------------------------------------------
!  moonmist.h
!  Outsources recurring code that does not necessarily change 
!  per game but is considered characteristic for a Moonmist 
!  release. This makes the main story file less cluttered with 
!  static code for better focus. Grammar and subs are grouped,
!  comment if a game doesn't make use of a certain feature.
!  
!  Copyright (c) 2023 Stefan Vogt, Moonmist Entertainment
!  http://8bitgames.itch.io
! ----------------------------------------------------------------------------

! recurring messages and conversations
Constant MESS_SCENERY "You needn't worry about that.";

 ! hic sunt dracones... trigger with 'aenima' magic verb in debug mode ------------------------------------
#ifdef DEBUG;
Verb 'aenima' * -> Cheatmode;
  [ CheatmodeSub;
    PROGRESS_LEVEL = 14;
    move snowstorm to Limbo;
    move Rosie to Limbo;
    stereosystem.player_progress = true;
    move electrictorch to player;
    give electrictorch on;
    give electrictorch light;
    move winterjacket to player;
    give winterjacket worn;
    move amulet to player;
    amulet.player_progress = true;
    give amulet worn;
    move Ysabella to OverGrownCemetery;
    move LordBain to Dovecote;
    move sleepingCora to Limbo;
    move opening to TheChapel;
    move entrance to Undercroft;
    Choice_Ending_Bad = false;
    move leatherbag to player;
    give leatherbag open;
    leatherbag.player_progress = true;
    move goldenkey to Limbo;
    move salt to leatherbag;
    move TheBoy to Limbo;
    move candles to player;
    move bloodlinen to player;
    move boxcutter to player;
    move lighter to player;
    move loafbread to player;
    move frankincense to player;
    SetFlag(F_Y_TALKED_FIRE);
    SetFlag(F_Y_TALKED_LIVING);
    SetFlag(F_Y_TALKED_DEAD);
    SetFlag(F_Y_TALKED_BLOOD);
    PlayerTo(OverGrownCemetery);
    MoveFloatingObjects();
  ];
#endif; 
! --------------------------------------------------------------------------------------------------------

! general grammar and enhancements
Verb meta 'continue' = 'again';
Verb      'credits' * -> Credits;
Verb      'xyzzy' * -> Xyzzy;
Extend    'rub' * noun 'with' held -> Rub;
Extend    'turn' * 'over' noun -> Turn;

Extend    'examine' * 'back' 'of' noun -> Turn
                 * 'the' 'back' 'of' noun -> Turn;

Extend    'look' * 'through'/'out' noun -> Examine;
Extend    'look' * 'out' 'of' noun -> Examine;
Extend    'attack' * held 'at'/'on' noun -> Attack;

Extend    'speak' replace
  * noun -> Talk
  * 'to'/'with' noun -> Talk;

Extend    'ask' replace
  * noun -> Talk
  * noun 'for' noun -> AskFor;

Verb 'grab' = 'take';
Verb 'kick' = 'attack';
Verb 'flip' = 'turn';
Verb 'consult' = 'open';

! --------------------------------------------------------------------------------------------------------

! the game's ABOUT grammar and sub
Verb 'about' * -> About;

[ AboutSub;
  print (string)Story, " is copyright (c) 2023 by Stefan Vogt and Moonmist Entertainment.^^You may freely distribute the game, but you have to link to ";
  ChangeFgColour(clr_emphasis_fg);
  print "<8bitgames.itch.io>"; 
  ChangeFgColour(clr_default_fg);
  print ". This work may not be sold or included in any for-profit collection without written permission from the author.^^Please send bug reports to ";
  ChangeFgColour(clr_emphasis_fg);
  print "<stefan@@64";
  print "8-bit.info>";
  ChangeFgColour(clr_default_fg);
  print ".^^For acknowledgements and credits, please type ";
  ChangeFgColour(clr_emphasis_fg);
  print "CREDITS";
  ChangeFgColour(clr_default_fg);
  ".";
];
! --------------------------------------------------------------------------------------------------------

! grammar and sub for the HELP command
Verb 'help' * -> Help;

[ HelpSub;
  print "Try to ";
  ChangeFgColour(clr_emphasis_fg);
  print "[examine]";
  ChangeFgColour(clr_default_fg);
  print " everything that is mentioned in room descriptions, otherwise you might miss important hints. Note that ";
  ChangeFgColour(clr_emphasis_fg);
  print "[examine]";
  ChangeFgColour(clr_default_fg);
  print " and ";
  ChangeFgColour(clr_emphasis_fg);
  print "[search]";
  ChangeFgColour(clr_default_fg);
  print " trigger different actions in this game.^^Your actions may also create different results based on the game's progress level. For example, why would you ";
  ChangeFgColour(clr_emphasis_fg);
  print "[dig]";
  ChangeFgColour(clr_default_fg);
  print " something if you don't know what you're looking for? If you ";
  ChangeFgColour(clr_emphasis_fg);
  print "[examine]";
  ChangeFgColour(clr_default_fg);
  print " a certain object, it could reveal new information once you found out something in the course of the game.^^The game's package contains a PlayIF card that explains basic gameplay and many synonyms will enhance what you read on it.^^Conversations are not as complex as in Infocom titles. It is sufficient to type ";
  ChangeFgColour(clr_emphasis_fg);
  print "[talk to NPC]";
  ChangeFgColour(clr_default_fg);
  print " or ";
  ChangeFgColour(clr_emphasis_fg);
  print "[ask NPC]";
  ChangeFgColour(clr_default_fg);
  print ".^^Use the ";
  ChangeFgColour(clr_emphasis_fg);
  print "[save]";
  ChangeFgColour(clr_default_fg);
  print " command to store your progress and ";
  ChangeFgColour(clr_emphasis_fg);
  print "[restore]";
  ChangeFgColour(clr_default_fg);
  " to load it again.";
];
! --------------------------------------------------------------------------------------------------------

! adding support for TURN AROUND as TURN YOURSELF synonym
Extend 'turn' * 'around' -> TurnAround;

[ TurnAroundSub;
  <<Turn player>>;
];
! --------------------------------------------------------------------------------------------------------

! sub and grammar for the unsupported USE verb
Verb 'use' * -> Use
           * noun -> Use
           * noun 'with'/'on'/'in'/'at' noun -> Use;

[ UseSub;
  print "This game does not support the ";
  ChangeFgColour(clr_emphasis_fg);
  print "[use]";
  ChangeFgColour(clr_default_fg);
  " verb. You need to be more specific.";
];
! --------------------------------------------------------------------------------------------------------

! if the game is compiled in Z-machine v3 format, UNDO is not available
#ifV3;
Verb 'undo' * -> Undo;

[ UndoSub;
  "This version of the game does not support the [undo] command.";
];
#endif;
! --------------------------------------------------------------------------------------------------------

! extending unlock to make unlocking with a key default
! Extend 'unlock' first * noun -> UnlockWithoutKey;

! [ UnlockWithoutKeySub;
!   if (noun has lockable) print_ret "Try being more specific. You probably want to unlock ", (the) noun, " with a certain object?";
!   "You cannot unlock this object.";
! ];
! --------------------------------------------------------------------------------------------------------

! extending LOOK with LOOK UNDER
Extend 'look' * 'under' noun -> LookUnder;

[ LookUnderSub;
  print "You don't have to look under any objects in this game. The only two verbs you need in this context are ";
  ChangeFgColour(clr_emphasis_fg);
  print "[examine]";
  ChangeFgColour(clr_default_fg); 
  print " and "; 
  ChangeFgColour(clr_emphasis_fg);
  print "[search]";
  ChangeFgColour(clr_default_fg);
  ".";
];
! --------------------------------------------------------------------------------------------------------

! replacing FILL with a custom implementation
Extend 'fill' replace
  * -> FillError
  * noun -> FillError
  * held 'with' noun -> Fill
  * noun 'in'/'into' held -> Fill;

Verb 'pour' = 'fill';
Verb 'spill' = 'fill';

[ FillSub;
  "You are not referring to an object that supports being filled with something in this game.";
];

[ FillErrorSub;
  print "The fill command wants you to be more specific: ";
  ChangeFgColour(clr_emphasis_fg);
  print "[fill object with something]";
  ChangeFgColour(clr_default_fg);
  ".";
];
! --------------------------------------------------------------------------------------------------------

! replacing DIG with a custom implementation
Extend 'dig' replace
  * -> DigError
	* noun -> DigError
	* noun 'with' held -> Dig;

[ DigSub;
  "That's not something you can dig in this game.";
];

[ DigErrorSub;
  print "The dig command wants you to be more specific: ";
  ChangeFgColour(clr_emphasis_fg);
  print "[dig something with object]";
  ChangeFgColour(clr_default_fg);
  ".";
];
! --------------------------------------------------------------------------------------------------------

! replacing BURN with a custom implementation
Verb 'burn' 
  * noun -> Burn
  * 'up' noun -> Burn
  * noun 'with' held -> Burn;

Verb 'flick' = 'burn';
Verb 'ignite' = 'burn';
Verb 'light' = 'burn';

[ BurnSub;
	if(ImplicitGrabIfNotHeld(second)) rtrue;
	"As much as you enjoyed burning things down when you were a kid, it would achieve nothing here.";
];
! --------------------------------------------------------------------------------------------------------

! adding KISS from Puny's extended verbset
Verb 'kiss' * -> Kiss
            * noun -> Kiss;

[ KissSub;
  "Excellent idea. Let's just make out with literally everything and everyone you come across.";
];
! --------------------------------------------------------------------------------------------------------
