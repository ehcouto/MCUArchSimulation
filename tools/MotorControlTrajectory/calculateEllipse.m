function [X,Y] = calculateEllipse(x, y, a, b)
    %# This functions returns points to draw an ellipse
    %#
    %#  @param x     X coordinate
    %#  @param y     Y coordinate
    %#  @param a     Semimajor axis
    %#  @param b     Semiminor axis
    %#
    angle = [0:0.01:2*pi]';
    sinalpha = sin(angle);
    cosalpha = cos(angle);

    X = x + (a * cosalpha);
    Y = y + (b * sinalpha);

    if nargout==1, X = [X Y]; end
end