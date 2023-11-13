! ----------------------------------------------------------------------------
!  minihacks.h
!  Contains Puny built-in routine replacements and supplements.
!  Comment to turn off features not needed for current game.
!  
!  Copyright (c) 2023 Stefan Vogt, Moonmist Entertainment
!  http://8bitgames.itch.io
! ----------------------------------------------------------------------------

! Puny built-in routine overrides (implementation see moonmist.h)
!Replace TakeSub;
Replace DigSub;
Replace FillSub;
Replace ConsultSub;
Replace ListenSub;
!Replace ThrowAtSub;
Replace SmellSub;
!Replace TieSub;
Replace AttackSub;

! Puny library messages overrides
Constant MSG_PROMPT 1000;
Constant MSG_DROP_DROPPED 1001;
Constant MSG_PARSER_NO_INPUT 1002;
Constant MSG_PARSER_UNKNOWN_VERB 1003;
Constant MSG_PARSER_DONT_UNDERSTAND_WORD 1004;
Constant MSG_LOOK_BEFORE_ROOMNAME 1005;
Constant MSG_PARSER_NO_NEED_REFER_TO 1006;
Constant MSG_FILL_NO_WATER 1007;
Constant MSG_PUSH_DEFAULT 1008;
Constant MSG_PULL_DEFAULT 1009;
Constant MSG_TURN_DEFAULT 1010;
Constant MSG_PUSHDIR_DEFAULT 1011;

[LibraryMessages p_msg p_arg_1 p_arg_2;
 switch(p_msg) {
    MSG_PROMPT:
      print ">";
      p_arg_1 = p_arg_2;
    MSG_DROP_DROPPED:
      print (The) noun, " fall";
      if (noun hasnt pluralname) print "s";
      if (parent(player) has enterable && parent(player) hasnt supporter) print_ret " into ", (the) parent(player), ".";
      else print " onto ";
      if (parent(player) has supporter) print_ret (the) parent(player), ".";
      else "the ground.";
    MSG_PARSER_NO_INPUT:
      "You won't get very far without input.^";
    MSG_PARSER_UNKNOWN_VERB:
      "That's an unknown verb. Could you try something else?";
    MSG_PARSER_DONT_UNDERSTAND_WORD:
      print "This game understands many words but ";
			print "~";
			_PrintUnknownWord();
			print_ret "~ is unfortunately not one of them.";
    MSG_LOOK_BEFORE_ROOMNAME:
      @new_line; ! mimics Inform style location texts, disable for Infocom style
    MSG_PARSER_NO_NEED_REFER_TO:
      print_ret (string)MESS_SCENERY;
    MSG_PUSH_DEFAULT, MSG_PULL_DEFAULT, MSG_TURN_DEFAULT:
		  if (action == ##Push) print_ret "You give ", (the) noun, " a bit of a push.";
      if (action == ##Pull) print_ret "You yank at ", (the) noun, " but nothing noteworthy happens.";
      if (action == ##Turn) print_ret "Turning ", (the) noun, " has no apparent effect.";
    MSG_PUSHDIR_DEFAULT:
      print_ret (The) noun, " can't be pushed from place to place.";
   }
 rfalse;
];
! --------------------------------------------------------------------------------------------------------

! adding ROOM and OUTSIDE classes for locations, containing a dynamic wall object 
Class Room;
Class Outside;

Object walls "walls"
  with name 'wall' 'walls',
      description "You check the walls without gaining any new insights.",
      before [;
          Attack:
            "There surely is a better way to deal with frustration.";
          Turn:
            "The walls? Are you serious?";
          Push, Pull:
            "The walls won't move.";
      ],
      found_in [;
            if (location ofclass Room) rtrue;
            if (location ofclass Outside) rfalse;
      ],
  has scenery;

! --------------------------------------------------------------------------------------------------------

! replaces Puny's built-in DrawStatusLine, adds full color support and Infocom interpreter compatibility
#ifV5;
Replace DrawStatusLine;
[ DrawStatusLine width;
   _StatusLineHeight(statusline_height); @set_window 1; @set_cursor 1 1;
	! if (clr_on && clr_fgstatus > 1) {
	! 	@set_colour clr_fgstatus clr_bg;
	! }
   style reverse;
   width = 0->33;
   FastSpaces (width);
   @set_cursor 1 2; _PrintObjName(location);
  !  if (width > 76)
  !  {
	!    s1 = NumWidth(status_field_1);
	!    s2 = NumWidth(status_field_2);
	!    posa = width-26;
	!    @set_cursor 1 posa;
	!    print " Score: ", status_field_1;
	!    FastSpaces(6-s1);
  !      print "Moves: ", status_field_2;
	!    FastSpaces(6-s2);
  !  }
  !  else if (width > 39)
  !  {
	!    s1 = NumWidth(status_field_1);
	!    s2 = NumWidth(status_field_2);
	!    posa = width - 9 - s1 - s2;
	!    @set_cursor 1 posa;
	!    print " Score: ", status_field_1, "/", status_field_2;
	!    @print_char ' ';
  !  }
   @set_cursor 1 1;
	! if (clr_on && clr_fgstatus > 1) {
	! 	@set_colour clr_fg clr_bg;
	! }
   style roman; @set_window 0;
];

! [NumWidth num width;
! 	width = 1;
! 	if(num < 0) {
! 		width++;
! 		num = -num;
! 	}
! 	if(num >= 10)
! 	{
! 	   width++;
! 	   if(num >= 100)
! 	   {
! 		   width++;
! 		   if(num >= 1000)
! 		   {
! 			   width++;
! 		   }
! 	   }
! 	}
! 	return width;
! ];
#endif;
! --------------------------------------------------------------------------------------------------------

! cheap scenery SceneReply stub
[ SceneryReply;
    default:
        print_ret (string)MESS_SCENERY;
];
! --------------------------------------------------------------------------------------------------------

! adding support for referring to non-animate objects with "him" or "her"

! Replace PronounNotice; 
! Attribute male; ! set for non-animate objects you want to refer with "him"
! [ PronounNotice p_object;
! 	if (p_object == 0 or player or Directions) return;
! 	if (p_object has pluralname) {
!     themobj = p_object;
! 	}
!   else if (p_object has male or female or neuter) {
!     SetPronoun(p_object);
!   }
!   else if (p_object has animate) {
!     SetPronoun(p_object);
! 	}
!   else itobj = p_object;
! ];

! [ SetPronoun p_object;
!   if (p_object has female) herobj = p_object;
! 	else if (p_object has neuter) itobj = p_object;
! 	else himobj = p_object;
! ];

! --------------------------------------------------------------------------------------------------------
