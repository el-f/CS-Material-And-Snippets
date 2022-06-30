def check_generator(gen):
    """
    examines the status of a Python generator expression gen and returns 'Created', 'Started' or 'Finished'.
    use reflection / inspection.
    """
    if gen.gi_frame is None:
        return 'Finished'
    if gen.gi_frame.f_lasti == -1:
        return 'Created'
    return 'Started'

