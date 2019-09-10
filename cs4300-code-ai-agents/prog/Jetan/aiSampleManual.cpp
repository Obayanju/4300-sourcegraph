#include "aiSampleManual.h"
#include <cstdio>

namespace ai
{
  namespace Jetan
  {
    Manual::Manual( ai::Agent::Options *opts ) {
      SetName( "Manual" );
    }
    
    Manual::~Manual( ) {
    }
    
    ai::Agent::Action * Manual::Program( const ai::Agent::Percept * percept ) {
      ai::Jetan::Action *action = new ai::Jetan::Action;
      
      std::string board_str = percept->GetAtom( "BOARD" ).GetValue( );
      ai::Jetan::Board board( board_str );

      std::stringstream ss( percept->GetAtom( "PLAYER_NUMBER" ).GetValue( ) );
      int player = 0;
      ss >> player;

      const std::vector< ai::Jetan::MoveData > & moves = board.DetermineLegalMoves( player );
      
      if( moves.size( ) > 0 ) {
        std::cout << "Player: " << player << std::endl;
        std::cout << "Board: " << board_str << std::endl;
        
        bool done = false;
        while( !done ) {
          ai::Jetan::MoveData move;
          std::cout << "Move? from_row,from_column,to_row,to_column" << std::endl;
          std::string buf;
          std::getline( std::cin, buf );
          
          int from_row = -1, from_column = -1, to_row = -1, to_column = -1;
          std::stringstream ss( buf );
          ss >> from_row >> from_column >> to_row >> to_column;
          if( ss 
              && from_row >= 0 && from_column >= 0 && to_row >= 0 && to_column >= 0
              && from_row < 10 && from_column < 10 && to_row < 10 && to_column < 10 )
            {
              move.piece.x = from_column;
              move.piece.y = from_row;
              move.offset.dx = to_column - from_column;
              move.offset.dy = to_row - from_row;
              if( board.IsLegal( player, move ) ) {
                action->SetMove( move );
                action->SetCode( ai::Jetan::Action::MOVE );
                done = true;
              } // if legal
            } // if scanned
        } // while
      } else {
        /* no legal move */
        action->SetCode( ai::Jetan::Action::QUIT );
      }
      return action;
    }
  }
}
