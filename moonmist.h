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
Constant MESS_SCENERY "Don't worry about it.";

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
    move loafbread to leadcoffin;
    move frankincense to leadcoffin;
    move gravestone to OverGrownCemetery;
    move leadcoffin to OverGrownCemetery;
    move candles to gravestone;
    move bowl to OverGrownCemetery;
    move witchbook to player;
    candles.player_progress = true;
    SetFlag(F_Y_TALKED_FIRE);
    SetFlag(F_Y_TALKED_LIVING);
    SetFlag(F_Y_TALKED_DEAD);
    SetFlag(F_Y_TALKED_BLOOD);
    PlayerTo(bench);
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
Extend    'look' * 'around' -> Look;
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

! let's change Puny's TAKE sub since the standard behavior only allows basic replies
[ TakeSub inplayer;
  if (parent(noun) in player) inplayer = true;
	if(TryToTakeNoun() ~= false) rtrue;
  print "You take ", (the) noun;
  if (inplayer == true) print " out";
  else print " with you";
  ".";
];
! --------------------------------------------------------------------------------------------------------

! not particularly happy with Puny's STAND behavior, so we replace it with our own grammar
Extend 'stand' replace
	*                                           -> Stand
	* 'up'                                      -> Stand
	* 'on' noun                                 -> Enter;

[ StandSub;
  "You're already standing up.";
];
! --------------------------------------------------------------------------------------------------------

! replacing Puny's THROWAT an implementation loosly based on the Dialog standard lib
Verb 'toss' = 'throw';

[ ThrowAtSub;
	if(ObjectIsUntouchable(second)) return;
	if(ImplicitDisrobeIfWorn(noun)) rtrue;
	if(second > 1) {
#IfDef DEBUG;
		if(debug_flag & 1) print "(", (name) second, ").before()^";
#EndIf;
		action = ##ThrownAt;
		if (RunRoutines(second, before) ~= 0) { action = ##ThrowAt; rtrue; }
		action = ##ThrowAt;
	}
	if(RunLife(second,##ThrowAt) ~= 0) rfalse;
	print_ret "Throwing ", (the) noun, " at ", (the) second, " would achieve little.";
];

! --------------------------------------------------------------------------------------------------------

! replacing Puny's SMELL sub with an implementation adapted from Dialog

[ SmellSub;
	if(ObjectIsUntouchable(noun)) return;
	if(noun == nothing) "You sniff at the air, perceiving nothing that surprises you.";
  if (~~ noun == player) print (The) noun;
  else "You smell as fine as usual.";
  print " smell";
  if (noun hasnt pluralname) print "s";
  " as expected.";
];
! --------------------------------------------------------------------------------------------------------

! replacing FILL with a custom implementation
Extend 'fill' replace
  * -> FillError
  * noun -> FillError
  * noun 'with' noun -> Fill
  * noun 'in'/'into' noun -> Fill;

Verb 'pour' = 'fill';
Verb 'spill' = 'fill';

[ FillSub;
  "This object doesn't support being poured or filled.";
];

[ FillErrorSub;
  print "The ";
  print (verbname) verb_word;
  print " command wants you to be more specific: ";
  ChangeFgColour(clr_emphasis_fg);
  if (verb_word == 'fill') print "[fill object with something]";
  else print "[pour object in/into something]";
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
  "As much as you ~dig~ the idea, it would achieve nothing.";
];

[ DigErrorSub;
  print "The dig command wants you to be more specific: ";
  ChangeFgColour(clr_emphasis_fg);
  print "[dig something with object]";
  ChangeFgColour(clr_default_fg);
  ".";
];
! --------------------------------------------------------------------------------------------------------

! adding BURN from extended verbset using a custom implementation
Verb 'burn' 
  * noun -> Burn
  * noun 'with' noun -> Burn
  * 'up' noun -> Burn;

Verb 'flick' = 'burn';
Verb 'ignite' = 'burn';
Verb 'light' = 'burn';

[ BurnSub;
	if(ImplicitGrabIfNotHeld(second)) rtrue;
	"Your pyromania will get you nowhere here.";
];
! --------------------------------------------------------------------------------------------------------

! adding KISS verb, partly inherited from Dialog
Verb 'kiss' * -> Kiss
            * noun -> Kiss;

Verb 'hug' = 'kiss';
Verb 'embrace' = 'kiss';

[ KissSub;
  if(noun == nothing) "What is the target of your fondness tendencies?";
  if(noun == player) "Your feelings for yourself are primarily of a platonic nature.";
  if(noun has animate) print_ret (The) noun, " is unmoved by your display of affection.";
  print_ret "You practice some objectophilia with ", (the) noun, ".";
];
! --------------------------------------------------------------------------------------------------------

! LISTEN verb borrowed from the Dialog standard library and adapted to Inform
Extend 'listen' replace
	* -> Listen
	* 'to' noun -> Listen;

[ ListenSub;
  if (noun == nothing) print_ret(string)MSG_LISTEN_DEFAULT;
  if (noun == player) "You can hear the familiar rumble of your blood stream and the faint whine of your nervous system.";
  if (noun has animate) print_ret (The) noun, " is silent.";
  print_ret "You hear no particular sound coming from ", (the)noun, ".";
];
! --------------------------------------------------------------------------------------------------------

! adding WAVE from Puny's extended verbset
Verb 'wave' * -> WaveHands
	          * noun -> Wave;

[ WaveSub;
    if(parent(noun) ~= player) { PrintMsg(MSG_WAVE_NOTHOLDING, noun); rtrue; }
    print_ret "You wave ", (the) noun, " in the air, with no apparent consequences.";
];

[ WaveHandsSub;
	"You wave your hands in the air.";
];
! --------------------------------------------------------------------------------------------------------

! DANCE verb borrowed form the Dialog standard library and adapted to Inform
Verb 'dance' * -> Dance
             * 'with' noun -> Dance;

Verb 'jive' = 'dance';
Verb 'twirl' = 'dance';
Verb 'spin' = 'dance';

[ DanceSub;
	"You practise your moves.";
];
! --------------------------------------------------------------------------------------------------------

! SING verb borrowed form the Dialog standard library and adapted to Inform
Verb 'sing' * -> Sing
            * 'with' noun -> Sing;

Verb 'hum' = 'sing';

[ SingSub;
	"You hum a few notes.";
];
! --------------------------------------------------------------------------------------------------------

! TIE/ATTACH verb borrowed from the Dialog standard library and adapted to Inform

[ TieSub;
	if(second == nothing) "To what?";
  print_ret "There's no obvious way to attach ", (the) noun, " to ", (the) second, ".";
];
! --------------------------------------------------------------------------------------------------------

! subtle change to Puny's ATTACK implementation

[ AttackSub;
	if(ImplicitGrabIfNotHeld(second)) rtrue;
	if (ObjectIsUntouchable(noun)) return;
	if (noun has animate && RunLife(noun, ##Attack) ~= 0) rfalse;
	print_ret "You consider to ", (verbname) verb_word, " ", (the) noun, ", but reject the idea.";
];
! --------------------------------------------------------------------------------------------------------

! 
Verb 'squeeze' 'squash'
	* noun -> Squeeze;

[ SqueezeSub; ! Dialog standard: print_ret "You give ", (the) noun, " a bit of a squeeze.";
	if (ObjectIsUntouchable(noun)) return;
	if (noun has animate) print_ret "You have a dirty mind.";
  print_ret "Years of practice with ketchup bottles have made you a master squeezer. \
             Yet nothing happens as you give ", (the) noun, " a bit of a squeeze.";
];
! --------------------------------------------------------------------------------------------------------
