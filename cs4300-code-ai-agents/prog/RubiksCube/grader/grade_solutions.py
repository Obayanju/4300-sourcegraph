#!/usr/bin/env python3

import sys, re, os
import tempfile
import subprocess
import time

def process_one_run( input_stream ):
    full_cost = 0
    total_nodes_generated = 0
    max_nodes_stored = 0
    all_moves = ""
    for line in input_stream:
        line = line.strip()
        if not re.match( '^search ', line ):
            continue
        #              solved generated stored cost
        #search graph astar T 5 5 12 rotate  L L D' F B' L L F' B D' L L
        match = re.match( 'search ([^ ]+) ([^ ]+) ([TF]) ([0-9]+) ([0-9]+) ([0-9]+) rotate(.*)$', line )
        if not match:
            raise Exception( "The search line does not match the approved pattern.\n" + line )

        total_nodes_generated += int( match.group(4) )
        nodes_stored = int( match.group( 5 ) )
        if nodes_stored > max_nodes_stored:
            max_nodes_stored = nodes_stored
        cost = float(match.group( 6 ))
        moves = match.group( 7 ).strip()
        
        full_cost += cost
        if len(moves) > 0:
            moves += " "
        all_moves += moves

    return ( total_nodes_generated, max_nodes_stored, full_cost, "rotate " + all_moves )

def process_one_check( input_stream ):
    cube = ""
    for line in input_stream:
        line = line.strip()
        if not re.match( '^Cube: ', line ):
            continue
        words = line.split()
        if len(words) != 2:
            continue
        cube = words[1]
    return cube == 'wwwwwwwwwgggggggggrrrrrrrrrbbbbbbbbboooooooooyyyyyyyyy'

def usage( argv0 ):
    print( "usage: " + argv0 + " command_script cube_file [cube_solver_program] [cube_solver_checker]" )
    print( "command_script is the command file with instructions search for solutions.\n",
           "   Its name and any file it runs must have a path relative to the current\n",
           "   working directory.")
    print( "cube_file is a file with one scrambled cube per line." )
    print( "cube_solver_program is assumed to be ./RubiksCubeSolver, if not specified.\n",
           "   The path specified must be relative to the current working directory.")
    print( "cube_solver_checker is assumed to be the same as cube_solver_program, unless\n"
           "   both are specified.  The path specified must be relative to the current\n"
           "   working directory.")
    sys.exit(1)
    return

def parse_args( argv ):
    if len(argv) < 3:
        usage(argv[0])

    command_script = argv[1]
    cube_file = argv[2]
    if len(argv) > 3:
        cube_solver_program = argv[3]
    else:
        cube_solver_program = "./RubiksCubeSolver"
    if len(argv) > 4:
        cube_solver_checker = argv[4]
    else:
        cube_solver_checker = cube_solver_program
    if cube_solver_program.find( "/" ) == -1:
        cube_solver_program = "./" + cube_solver_program
    if cube_solver_checker.find( "/" ) == -1:
        cube_solver_checker = "./" + cube_solver_checker

    error = 0
    if not os.path.exists( command_script ):
        print( command_script + " does not exist." )
        error += 1
    if not os.path.exists( cube_file ):
        print( cube_file + " does not exist." )
        error += 1
    if not os.path.exists( cube_solver_program ):
        print( cube_solver_program + " does not exist." )
        error += 1
    if not os.path.exists( cube_solver_checker ):
        print( cube_solver_checker + " does not exist." )
        error += 1
    if error > 0:
        usage(argv[0])        

    return command_script, cube_file, cube_solver_program, cube_solver_checker

def build_solve_script( command_script, cube ):

    s = """
config enable_prompt 0
echo
#
#
init cube """ + cube + """
#
#
run """ + command_script + """
#
config cube_display 3
show cube
"""
    return s

def build_check_script( cube, commands ):
    s = """
config enable_prompt 0
echo
#
#
init cube """ + cube + """
#
#
""" + commands + """
#
config cube_display 2
show cube
"""
    return s


def run_solve_script( command_script, cube, cube_solver_program ):
    solve_commands = build_solve_script( command_script, cube )
    args = [ cube_solver_program ]
    results = subprocess.run(args, input=solve_commands.encode('utf-8'), stdout=subprocess.PIPE)
    lines = results.stdout.decode('utf-8').split('\n')
    return process_one_run( lines )

def run_solution( cube, commands, cube_solver_checker ):
    check_commands = build_check_script( cube, commands )

    args = [ cube_solver_checker ]
    results = subprocess.run(args, input=check_commands.encode('utf-8'), stdout=subprocess.PIPE)
    lines = results.stdout.decode('utf-8').split('\n')
    return process_one_check( lines )

def process_one_cube( command_script, cube, cube_solver_program, cube_solver_checker ):
    total_nodes_generated, max_nodes_stored, full_cost, commands = run_solve_script( command_script, cube, cube_solver_program )
    solved = run_solution( cube, commands, cube_solver_checker )
    if not solved:
        print( "cube not solved by commands: " + cube )
    else:
        print( total_nodes_generated, max_nodes_stored, full_cost, commands )
    return total_nodes_generated, max_nodes_stored, full_cost, solved

def process_all_cubes( command_script, cube_file, cube_solver_program, cube_solver_checker ):
    t0 = time.time()
    generated = 0
    stored = 0
    cost = 0
    solved = 0
    count = 0
    fin = open(cube_file, "r")
    for line in fin:
        cube = line.strip()
        total_nodes_generated, max_nodes_stored, cost0, solved0 = process_one_cube( command_script, cube, cube_solver_program, cube_solver_checker )
        generated += total_nodes_generated
        stored += max_nodes_stored
        cost += cost0
        if solved0:
            solved += 1
        count += 1
    fin.close()
    t1 = time.time()
    dt = t1 - t0
    failed_fraction = 1.0 - (solved/count)
    failed_penalty = 60*10 # 10 minutes
    score1 = ((cost/count) * 1.) + (dt/count) + failed_fraction * failed_penalty
    score2 = ((cost/count) * 1.) + (generated/count)*(10**-5) + failed_fraction * failed_penalty
    print( "Average generated: " + str(generated/count) )
    print( "Average stored: " + str(stored/count) )
    print( "Average cost: " + str(cost/count) )
    print( "Average time: " + str(dt/count) )
    print( "Solve fraction: " + str(solved/count) )
    print( "Score1: " + str(score1) )
    print( "Score2: " + str(score2) )
    return

def main( argv ):
    command_script, cube_file, cube_solver_program, cube_solver_checker = parse_args( argv )
    process_all_cubes( command_script, cube_file, cube_solver_program, cube_solver_checker )
    return

if __name__ == "__main__":
    main( sys.argv )
