# Introduction #

Kiess aiming at a "Who's who?" like game playable in network via xmpp.
Team game will be supported and the max players count per server will be 2 for single player game or 4 for team game.
Users are recognize via their jabber id.

# Game cutting edge #

  * Full screen graphics view game
  * 2 or 4 players (temates) per hub - no IA in development stage
  * xmpp identification and game protocol
  * sound player
  * interchangeable cards pack with cards properties global to a cards set

# Parts to develop #

  * [Gui](Gui.md) (QtGui/QGraphicsView)
  * [GameView](GameView.md) (QGraphicsView)
  * Cards packs (QtCore)
  * Network (QtCore/Xmpp)
  * Sound (Phonon)