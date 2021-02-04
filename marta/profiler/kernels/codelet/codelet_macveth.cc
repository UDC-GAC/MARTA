/* begin INFO MACVETH: headers added */
#include <immintrin.h>
/* end INFO MACVETH */
#include "codelet.h"

#define restrict __restrict

void codelet(double *restrict A, double *restrict x, double *restrict y) {
  register int i0, i1, i2, i3, i4, i5, i6;

#pragma macveth
  __m256d __mv_vop2, __mv_vop0, __mv_vop1, __mv_vop5, __mv_vop3, __mv_vop4,
      __mv_vop1542, __mv_vop1543, __mv_vop8, __mv_vop6, __mv_vop7, __mv_vop11,
      __mv_vop9, __mv_vop10, __mv_vop1544, __mv_vop1545, __mv_vop14, __mv_vop12,
      __mv_vop13, __mv_vop17, __mv_vop15, __mv_vop16, __mv_vop1546,
      __mv_vop1547, __mv_vop20, __mv_vop18, __mv_vop19, __mv_vop23, __mv_vop21,
      __mv_vop22, __mv_vop1548, __mv_vop1549, __mv_vop26, __mv_vop24,
      __mv_vop25, __mv_vop29, __mv_vop27, __mv_vop28, __mv_vop1550,
      __mv_vop1551, __mv_vop32, __mv_vop30, __mv_vop31, __mv_vop35, __mv_vop33,
      __mv_vop34, __mv_vop1552, __mv_vop1553, __mv_vop38, __mv_vop36,
      __mv_vop37, __mv_vop41, __mv_vop39, __mv_vop40, __mv_vop1554,
      __mv_vop1555, __mv_vop44, __mv_vop42, __mv_vop43, __mv_vop47, __mv_vop45,
      __mv_vop46, __mv_vop1556, __mv_vop1557, __mv_vop50, __mv_vop48,
      __mv_vop49, __mv_vop53, __mv_vop51, __mv_vop52, __mv_vop1558,
      __mv_vop1559, __mv_vop56, __mv_vop54, __mv_vop55, __mv_vop59, __mv_vop57,
      __mv_vop58, __mv_vop1560, __mv_vop1561, __mv_vop62, __mv_vop60,
      __mv_vop61, __mv_vop65, __mv_vop63, __mv_vop64, __mv_vop1562,
      __mv_vop1563, __mv_vop68, __mv_vop66, __mv_vop67, __mv_vop71, __mv_vop69,
      __mv_vop70, __mv_vop1564, __mv_vop1565, __mv_vop74, __mv_vop72,
      __mv_vop73, __mv_vop77, __mv_vop75, __mv_vop76, __mv_vop1566,
      __mv_vop1567, __mv_vop80, __mv_vop78, __mv_vop79, __mv_vop83, __mv_vop81,
      __mv_vop82, __mv_vop1568, __mv_vop1569, __mv_vop86, __mv_vop84,
      __mv_vop85, __mv_vop89, __mv_vop87, __mv_vop88, __mv_vop1570,
      __mv_vop1571, __mv_vop92, __mv_vop90, __mv_vop91, __mv_vop95, __mv_vop93,
      __mv_vop94, __mv_vop1572, __mv_vop1573, __mv_vop98, __mv_vop96,
      __mv_vop97, __mv_vop101, __mv_vop99, __mv_vop100, __mv_vop1574,
      __mv_vop1575, __mv_vop104, __mv_vop102, __mv_vop103, __mv_vop107,
      __mv_vop105, __mv_vop106, __mv_vop1576, __mv_vop1577, __mv_vop110,
      __mv_vop108, __mv_vop109, __mv_vop113, __mv_vop111, __mv_vop112,
      __mv_vop1578, __mv_vop1579, __mv_vop116, __mv_vop114, __mv_vop115,
      __mv_vop119, __mv_vop117, __mv_vop118, __mv_vop1580, __mv_vop1581,
      __mv_vop122, __mv_vop120, __mv_vop121, __mv_vop125, __mv_vop123,
      __mv_vop124, __mv_vop1582, __mv_vop1583, __mv_vop128, __mv_vop126,
      __mv_vop127, __mv_vop131, __mv_vop129, __mv_vop130, __mv_vop1584,
      __mv_vop1585, __mv_vop134, __mv_vop132, __mv_vop133, __mv_vop137,
      __mv_vop135, __mv_vop136, __mv_vop1586, __mv_vop1587, __mv_vop140,
      __mv_vop138, __mv_vop139, __mv_vop143, __mv_vop141, __mv_vop142,
      __mv_vop1588, __mv_vop1589, __mv_vop146, __mv_vop144, __mv_vop145,
      __mv_vop149, __mv_vop147, __mv_vop148, __mv_vop1590, __mv_vop1591,
      __mv_vop152, __mv_vop150, __mv_vop151, __mv_vop155, __mv_vop153,
      __mv_vop154, __mv_vop1592, __mv_vop1593, __mv_vop158, __mv_vop156,
      __mv_vop157, __mv_vop161, __mv_vop159, __mv_vop160, __mv_vop1594,
      __mv_vop1595, __mv_vop164, __mv_vop162, __mv_vop163, __mv_vop167,
      __mv_vop165, __mv_vop166, __mv_vop1596, __mv_vop1597, __mv_vop170,
      __mv_vop168, __mv_vop169, __mv_vop173, __mv_vop171, __mv_vop172,
      __mv_vop1598, __mv_vop1599, __mv_vop176, __mv_vop174, __mv_vop175,
      __mv_vop179, __mv_vop177, __mv_vop178, __mv_vop1600, __mv_vop1601,
      __mv_vop182, __mv_vop180, __mv_vop181, __mv_vop185, __mv_vop183,
      __mv_vop184, __mv_vop1602, __mv_vop1603, __mv_vop188, __mv_vop186,
      __mv_vop187, __mv_vop191, __mv_vop189, __mv_vop190, __mv_vop1604,
      __mv_vop1605, __mv_vop194, __mv_vop192, __mv_vop193, __mv_vop197,
      __mv_vop195, __mv_vop196, __mv_vop1606, __mv_vop1607, __mv_vop200,
      __mv_vop198, __mv_vop199, __mv_vop203, __mv_vop201, __mv_vop202,
      __mv_vop1608, __mv_vop1609, __mv_vop206, __mv_vop204, __mv_vop205,
      __mv_vop209, __mv_vop207, __mv_vop208, __mv_vop1610, __mv_vop1611,
      __mv_vop212, __mv_vop210, __mv_vop211, __mv_vop215, __mv_vop213,
      __mv_vop214, __mv_vop1612, __mv_vop1613, __mv_vop218, __mv_vop216,
      __mv_vop217, __mv_vop221, __mv_vop219, __mv_vop220, __mv_vop1614,
      __mv_vop1615, __mv_vop224, __mv_vop222, __mv_vop223, __mv_vop227,
      __mv_vop225, __mv_vop226, __mv_vop1616, __mv_vop1617, __mv_vop230,
      __mv_vop228, __mv_vop229, __mv_vop233, __mv_vop231, __mv_vop232,
      __mv_vop1618, __mv_vop1619, __mv_vop236, __mv_vop234, __mv_vop235,
      __mv_vop239, __mv_vop237, __mv_vop238, __mv_vop1620, __mv_vop1621,
      __mv_vop242, __mv_vop240, __mv_vop241, __mv_vop245, __mv_vop243,
      __mv_vop244, __mv_vop1622, __mv_vop1623, __mv_vop248, __mv_vop246,
      __mv_vop247, __mv_vop251, __mv_vop249, __mv_vop250, __mv_vop1624,
      __mv_vop1625, __mv_vop254, __mv_vop252, __mv_vop253, __mv_vop257,
      __mv_vop255, __mv_vop256, __mv_vop1626, __mv_vop1627, __mv_vop260,
      __mv_vop258, __mv_vop259, __mv_vop263, __mv_vop261, __mv_vop262,
      __mv_vop1628, __mv_vop1629, __mv_vop266, __mv_vop264, __mv_vop265,
      __mv_vop269, __mv_vop267, __mv_vop268, __mv_vop1630, __mv_vop1631,
      __mv_vop272, __mv_vop270, __mv_vop271, __mv_vop275, __mv_vop273,
      __mv_vop274, __mv_vop1632, __mv_vop1633, __mv_vop278, __mv_vop276,
      __mv_vop277, __mv_vop281, __mv_vop279, __mv_vop280, __mv_vop1634,
      __mv_vop1635, __mv_vop284, __mv_vop282, __mv_vop283, __mv_vop287,
      __mv_vop285, __mv_vop286, __mv_vop1636, __mv_vop1637, __mv_vop290,
      __mv_vop288, __mv_vop289, __mv_vop293, __mv_vop291, __mv_vop292,
      __mv_vop1638, __mv_vop1639, __mv_vop296, __mv_vop294, __mv_vop295,
      __mv_vop299, __mv_vop297, __mv_vop298, __mv_vop1640, __mv_vop1641,
      __mv_vop302, __mv_vop300, __mv_vop301, __mv_vop305, __mv_vop303,
      __mv_vop304, __mv_vop1642, __mv_vop1643, __mv_vop308, __mv_vop306,
      __mv_vop307, __mv_vop311, __mv_vop309, __mv_vop310, __mv_vop1644,
      __mv_vop1645, __mv_vop314, __mv_vop312, __mv_vop313, __mv_vop317,
      __mv_vop315, __mv_vop316, __mv_vop1646, __mv_vop1647, __mv_vop320,
      __mv_vop318, __mv_vop319, __mv_vop323, __mv_vop321, __mv_vop322,
      __mv_vop1648, __mv_vop1649, __mv_vop326, __mv_vop324, __mv_vop325,
      __mv_vop329, __mv_vop327, __mv_vop328, __mv_vop1650, __mv_vop1651,
      __mv_vop332, __mv_vop330, __mv_vop331, __mv_vop335, __mv_vop333,
      __mv_vop334, __mv_vop1652, __mv_vop1653, __mv_vop338, __mv_vop336,
      __mv_vop337, __mv_vop341, __mv_vop339, __mv_vop340, __mv_vop1654,
      __mv_vop1655, __mv_vop344, __mv_vop342, __mv_vop343, __mv_vop347,
      __mv_vop345, __mv_vop346, __mv_vop1656, __mv_vop1657, __mv_vop350,
      __mv_vop348, __mv_vop349, __mv_vop353, __mv_vop351, __mv_vop352,
      __mv_vop1658, __mv_vop1659, __mv_vop356, __mv_vop354, __mv_vop355,
      __mv_vop359, __mv_vop357, __mv_vop358, __mv_vop1660, __mv_vop1661,
      __mv_vop362, __mv_vop360, __mv_vop361, __mv_vop365, __mv_vop363,
      __mv_vop364, __mv_vop1662, __mv_vop1663, __mv_vop368, __mv_vop366,
      __mv_vop367, __mv_vop371, __mv_vop369, __mv_vop370, __mv_vop1664,
      __mv_vop1665, __mv_vop374, __mv_vop372, __mv_vop373, __mv_vop377,
      __mv_vop375, __mv_vop376, __mv_vop1666, __mv_vop1667, __mv_vop380,
      __mv_vop378, __mv_vop379, __mv_vop383, __mv_vop381, __mv_vop382,
      __mv_vop1668, __mv_vop1669, __mv_vop386, __mv_vop384, __mv_vop385,
      __mv_vop389, __mv_vop387, __mv_vop388, __mv_vop1670, __mv_vop1671,
      __mv_vop392, __mv_vop390, __mv_vop391, __mv_vop395, __mv_vop393,
      __mv_vop394, __mv_vop1672, __mv_vop1673, __mv_vop398, __mv_vop396,
      __mv_vop397, __mv_vop401, __mv_vop399, __mv_vop400, __mv_vop1674,
      __mv_vop1675, __mv_vop404, __mv_vop402, __mv_vop403, __mv_vop407,
      __mv_vop405, __mv_vop406, __mv_vop1676, __mv_vop1677, __mv_vop410,
      __mv_vop408, __mv_vop409, __mv_vop413, __mv_vop411, __mv_vop412,
      __mv_vop1678, __mv_vop1679, __mv_vop416, __mv_vop414, __mv_vop415,
      __mv_vop419, __mv_vop417, __mv_vop418, __mv_vop1680, __mv_vop1681,
      __mv_vop422, __mv_vop420, __mv_vop421, __mv_vop425, __mv_vop423,
      __mv_vop424, __mv_vop1682, __mv_vop1683, __mv_vop428, __mv_vop426,
      __mv_vop427, __mv_vop431, __mv_vop429, __mv_vop430, __mv_vop1684,
      __mv_vop1685, __mv_vop434, __mv_vop432, __mv_vop433, __mv_vop437,
      __mv_vop435, __mv_vop436, __mv_vop1686, __mv_vop1687, __mv_vop440,
      __mv_vop438, __mv_vop439, __mv_vop443, __mv_vop441, __mv_vop442,
      __mv_vop1688, __mv_vop1689, __mv_vop446, __mv_vop444, __mv_vop445,
      __mv_vop449, __mv_vop447, __mv_vop448, __mv_vop1690, __mv_vop1691,
      __mv_vop452, __mv_vop450, __mv_vop451, __mv_vop455, __mv_vop453,
      __mv_vop454, __mv_vop1692, __mv_vop1693, __mv_vop458, __mv_vop456,
      __mv_vop457, __mv_vop461, __mv_vop459, __mv_vop460, __mv_vop1694,
      __mv_vop1695, __mv_vop464, __mv_vop462, __mv_vop463, __mv_vop467,
      __mv_vop465, __mv_vop466, __mv_vop1696, __mv_vop1697, __mv_vop470,
      __mv_vop468, __mv_vop469, __mv_vop473, __mv_vop471, __mv_vop472,
      __mv_vop1698, __mv_vop1699, __mv_vop476, __mv_vop474, __mv_vop475,
      __mv_vop479, __mv_vop477, __mv_vop478, __mv_vop1700, __mv_vop1701,
      __mv_vop482, __mv_vop480, __mv_vop481, __mv_vop485, __mv_vop483,
      __mv_vop484, __mv_vop1702, __mv_vop1703, __mv_vop488, __mv_vop486,
      __mv_vop487, __mv_vop491, __mv_vop489, __mv_vop490, __mv_vop1704,
      __mv_vop1705, __mv_vop494, __mv_vop492, __mv_vop493, __mv_vop497,
      __mv_vop495, __mv_vop496, __mv_vop1706, __mv_vop1707, __mv_vop500,
      __mv_vop498, __mv_vop499, __mv_vop503, __mv_vop501, __mv_vop502,
      __mv_vop1708, __mv_vop1709, __mv_vop506, __mv_vop504, __mv_vop505,
      __mv_vop509, __mv_vop507, __mv_vop508, __mv_vop1710, __mv_vop1711,
      __mv_vop512, __mv_vop510, __mv_vop511, __mv_vop515, __mv_vop513,
      __mv_vop514, __mv_vop1712, __mv_vop1713, __mv_vop518, __mv_vop516,
      __mv_vop517, __mv_vop521, __mv_vop519, __mv_vop520, __mv_vop1714,
      __mv_vop1715, __mv_vop524, __mv_vop522, __mv_vop523, __mv_vop527,
      __mv_vop525, __mv_vop526, __mv_vop1716, __mv_vop1717, __mv_vop530,
      __mv_vop528, __mv_vop529, __mv_vop533, __mv_vop531, __mv_vop532,
      __mv_vop1718, __mv_vop1719, __mv_vop536, __mv_vop534, __mv_vop535,
      __mv_vop539, __mv_vop537, __mv_vop538, __mv_vop1720, __mv_vop1721,
      __mv_vop542, __mv_vop540, __mv_vop541, __mv_vop545, __mv_vop543,
      __mv_vop544, __mv_vop1722, __mv_vop1723, __mv_vop548, __mv_vop546,
      __mv_vop547, __mv_vop551, __mv_vop549, __mv_vop550, __mv_vop1724,
      __mv_vop1725, __mv_vop554, __mv_vop552, __mv_vop553, __mv_vop557,
      __mv_vop555, __mv_vop556, __mv_vop1726, __mv_vop1727, __mv_vop560,
      __mv_vop558, __mv_vop559, __mv_vop563, __mv_vop561, __mv_vop562,
      __mv_vop1728, __mv_vop1729, __mv_vop566, __mv_vop564, __mv_vop565,
      __mv_vop569, __mv_vop567, __mv_vop568, __mv_vop1730, __mv_vop1731,
      __mv_vop572, __mv_vop570, __mv_vop571, __mv_vop575, __mv_vop573,
      __mv_vop574, __mv_vop1732, __mv_vop1733, __mv_vop578, __mv_vop576,
      __mv_vop577, __mv_vop581, __mv_vop579, __mv_vop580, __mv_vop1734,
      __mv_vop1735, __mv_vop584, __mv_vop582, __mv_vop583, __mv_vop587,
      __mv_vop585, __mv_vop586, __mv_vop1736, __mv_vop1737, __mv_vop590,
      __mv_vop588, __mv_vop589, __mv_vop593, __mv_vop591, __mv_vop592,
      __mv_vop1738, __mv_vop1739, __mv_vop596, __mv_vop594, __mv_vop595,
      __mv_vop599, __mv_vop597, __mv_vop598, __mv_vop1740, __mv_vop1741,
      __mv_vop602, __mv_vop600, __mv_vop601, __mv_vop605, __mv_vop603,
      __mv_vop604, __mv_vop1742, __mv_vop1743, __mv_vop608, __mv_vop606,
      __mv_vop607, __mv_vop611, __mv_vop609, __mv_vop610, __mv_vop1744,
      __mv_vop1745, __mv_vop614, __mv_vop612, __mv_vop613, __mv_vop617,
      __mv_vop615, __mv_vop616, __mv_vop1746, __mv_vop1747, __mv_vop620,
      __mv_vop618, __mv_vop619, __mv_vop623, __mv_vop621, __mv_vop622,
      __mv_vop1748, __mv_vop1749, __mv_vop626, __mv_vop624, __mv_vop625,
      __mv_vop629, __mv_vop627, __mv_vop628, __mv_vop1750, __mv_vop1751,
      __mv_vop632, __mv_vop630, __mv_vop631, __mv_vop635, __mv_vop633,
      __mv_vop634, __mv_vop1752, __mv_vop1753, __mv_vop638, __mv_vop636,
      __mv_vop637, __mv_vop641, __mv_vop639, __mv_vop640, __mv_vop1754,
      __mv_vop1755, __mv_vop644, __mv_vop642, __mv_vop643, __mv_vop647,
      __mv_vop645, __mv_vop646, __mv_vop1756, __mv_vop1757, __mv_vop650,
      __mv_vop648, __mv_vop649, __mv_vop653, __mv_vop651, __mv_vop652,
      __mv_vop1758, __mv_vop1759, __mv_vop656, __mv_vop654, __mv_vop655,
      __mv_vop659, __mv_vop657, __mv_vop658, __mv_vop1760, __mv_vop1761,
      __mv_vop662, __mv_vop660, __mv_vop661, __mv_vop665, __mv_vop663,
      __mv_vop664, __mv_vop1762, __mv_vop1763, __mv_vop668, __mv_vop666,
      __mv_vop667, __mv_vop671, __mv_vop669, __mv_vop670, __mv_vop1764,
      __mv_vop1765, __mv_vop674, __mv_vop672, __mv_vop673, __mv_vop677,
      __mv_vop675, __mv_vop676, __mv_vop1766, __mv_vop1767, __mv_vop680,
      __mv_vop678, __mv_vop679, __mv_vop683, __mv_vop681, __mv_vop682,
      __mv_vop1768, __mv_vop1769, __mv_vop686, __mv_vop684, __mv_vop685,
      __mv_vop689, __mv_vop687, __mv_vop688, __mv_vop1770, __mv_vop1771,
      __mv_vop692, __mv_vop690, __mv_vop691, __mv_vop695, __mv_vop693,
      __mv_vop694, __mv_vop1772, __mv_vop1773, __mv_vop698, __mv_vop696,
      __mv_vop697, __mv_vop701, __mv_vop699, __mv_vop700, __mv_vop1774,
      __mv_vop1775, __mv_vop704, __mv_vop702, __mv_vop703, __mv_vop707,
      __mv_vop705, __mv_vop706, __mv_vop1776, __mv_vop1777, __mv_vop710,
      __mv_vop708, __mv_vop709, __mv_vop713, __mv_vop711, __mv_vop712,
      __mv_vop1778, __mv_vop1779, __mv_vop716, __mv_vop714, __mv_vop715,
      __mv_vop719, __mv_vop717, __mv_vop718, __mv_vop1780, __mv_vop1781,
      __mv_vop722, __mv_vop720, __mv_vop721, __mv_vop725, __mv_vop723,
      __mv_vop724, __mv_vop1782, __mv_vop1783, __mv_vop728, __mv_vop726,
      __mv_vop727, __mv_vop731, __mv_vop729, __mv_vop730, __mv_vop1784,
      __mv_vop1785, __mv_vop734, __mv_vop732, __mv_vop733, __mv_vop737,
      __mv_vop735, __mv_vop736, __mv_vop1786, __mv_vop1787, __mv_vop740,
      __mv_vop738, __mv_vop739, __mv_vop743, __mv_vop741, __mv_vop742,
      __mv_vop1788, __mv_vop1789, __mv_vop746, __mv_vop744, __mv_vop745,
      __mv_vop749, __mv_vop747, __mv_vop748, __mv_vop1790, __mv_vop1791,
      __mv_vop752, __mv_vop750, __mv_vop751, __mv_vop755, __mv_vop753,
      __mv_vop754, __mv_vop1792, __mv_vop1793, __mv_vop758, __mv_vop756,
      __mv_vop757, __mv_vop761, __mv_vop759, __mv_vop760, __mv_vop1794,
      __mv_vop1795, __mv_vop764, __mv_vop762, __mv_vop763, __mv_vop767,
      __mv_vop765, __mv_vop766, __mv_vop1796, __mv_vop1797, __mv_vop770,
      __mv_vop768, __mv_vop769, __mv_vop773, __mv_vop771, __mv_vop772,
      __mv_vop1798, __mv_vop1799, __mv_vop776, __mv_vop774, __mv_vop775,
      __mv_vop779, __mv_vop777, __mv_vop778, __mv_vop1800, __mv_vop1801,
      __mv_vop782, __mv_vop780, __mv_vop781, __mv_vop785, __mv_vop783,
      __mv_vop784, __mv_vop1802, __mv_vop1803, __mv_vop788, __mv_vop786,
      __mv_vop787, __mv_vop791, __mv_vop789, __mv_vop790, __mv_vop1804,
      __mv_vop1805, __mv_vop794, __mv_vop792, __mv_vop793, __mv_vop797,
      __mv_vop795, __mv_vop796, __mv_vop1806, __mv_vop1807, __mv_vop800,
      __mv_vop798, __mv_vop799, __mv_vop803, __mv_vop801, __mv_vop802,
      __mv_vop1808, __mv_vop1809, __mv_vop806, __mv_vop804, __mv_vop805,
      __mv_vop809, __mv_vop807, __mv_vop808, __mv_vop1810, __mv_vop1811,
      __mv_vop812, __mv_vop810, __mv_vop811, __mv_vop815, __mv_vop813,
      __mv_vop814, __mv_vop1812, __mv_vop1813, __mv_vop818, __mv_vop816,
      __mv_vop817, __mv_vop821, __mv_vop819, __mv_vop820, __mv_vop1814,
      __mv_vop1815, __mv_vop824, __mv_vop822, __mv_vop823, __mv_vop827,
      __mv_vop825, __mv_vop826, __mv_vop1816, __mv_vop1817, __mv_vop830,
      __mv_vop828, __mv_vop829, __mv_vop833, __mv_vop831, __mv_vop832,
      __mv_vop1818, __mv_vop1819, __mv_vop836, __mv_vop834, __mv_vop835,
      __mv_vop839, __mv_vop837, __mv_vop838, __mv_vop1820, __mv_vop1821,
      __mv_vop842, __mv_vop840, __mv_vop841, __mv_vop845, __mv_vop843,
      __mv_vop844, __mv_vop1822, __mv_vop1823, __mv_vop848, __mv_vop846,
      __mv_vop847, __mv_vop851, __mv_vop849, __mv_vop850, __mv_vop1824,
      __mv_vop1825, __mv_vop854, __mv_vop852, __mv_vop853, __mv_vop857,
      __mv_vop855, __mv_vop856, __mv_vop1826, __mv_vop1827, __mv_vop860,
      __mv_vop858, __mv_vop859, __mv_vop863, __mv_vop861, __mv_vop862,
      __mv_vop1828, __mv_vop1829, __mv_vop866, __mv_vop864, __mv_vop865,
      __mv_vop869, __mv_vop867, __mv_vop868, __mv_vop1830, __mv_vop1831,
      __mv_vop872, __mv_vop870, __mv_vop871, __mv_vop875, __mv_vop873,
      __mv_vop874, __mv_vop1832, __mv_vop1833, __mv_vop878, __mv_vop876,
      __mv_vop877, __mv_vop881, __mv_vop879, __mv_vop880, __mv_vop1834,
      __mv_vop1835, __mv_vop884, __mv_vop882, __mv_vop883, __mv_vop887,
      __mv_vop885, __mv_vop886, __mv_vop1836, __mv_vop1837, __mv_vop890,
      __mv_vop888, __mv_vop889, __mv_vop893, __mv_vop891, __mv_vop892,
      __mv_vop1838, __mv_vop1839, __mv_vop896, __mv_vop894, __mv_vop895,
      __mv_vop899, __mv_vop897, __mv_vop898, __mv_vop1840, __mv_vop1841,
      __mv_vop902, __mv_vop900, __mv_vop901, __mv_vop905, __mv_vop903,
      __mv_vop904, __mv_vop1842, __mv_vop1843, __mv_vop908, __mv_vop906,
      __mv_vop907, __mv_vop911, __mv_vop909, __mv_vop910, __mv_vop1844,
      __mv_vop1845, __mv_vop914, __mv_vop912, __mv_vop913, __mv_vop917,
      __mv_vop915, __mv_vop916, __mv_vop1846, __mv_vop1847, __mv_vop920,
      __mv_vop918, __mv_vop919, __mv_vop923, __mv_vop921, __mv_vop922,
      __mv_vop1848, __mv_vop1849, __mv_vop926, __mv_vop924, __mv_vop925,
      __mv_vop929, __mv_vop927, __mv_vop928, __mv_vop1850, __mv_vop1851,
      __mv_vop932, __mv_vop930, __mv_vop931, __mv_vop935, __mv_vop933,
      __mv_vop934, __mv_vop1852, __mv_vop1853, __mv_vop938, __mv_vop936,
      __mv_vop937, __mv_vop941, __mv_vop939, __mv_vop940, __mv_vop1854,
      __mv_vop1855, __mv_vop944, __mv_vop942, __mv_vop943, __mv_vop947,
      __mv_vop945, __mv_vop946, __mv_vop1856, __mv_vop1857, __mv_vop950,
      __mv_vop948, __mv_vop949, __mv_vop953, __mv_vop951, __mv_vop952,
      __mv_vop1858, __mv_vop1859, __mv_vop956, __mv_vop954, __mv_vop955,
      __mv_vop959, __mv_vop957, __mv_vop958, __mv_vop1860, __mv_vop1861,
      __mv_vop962, __mv_vop960, __mv_vop961, __mv_vop965, __mv_vop963,
      __mv_vop964, __mv_vop1862, __mv_vop1863, __mv_vop968, __mv_vop966,
      __mv_vop967, __mv_vop971, __mv_vop969, __mv_vop970, __mv_vop1864,
      __mv_vop1865, __mv_vop974, __mv_vop972, __mv_vop973, __mv_vop977,
      __mv_vop975, __mv_vop976, __mv_vop1866, __mv_vop1867, __mv_vop980,
      __mv_vop978, __mv_vop979, __mv_vop983, __mv_vop981, __mv_vop982,
      __mv_vop1868, __mv_vop1869, __mv_vop986, __mv_vop984, __mv_vop985,
      __mv_vop989, __mv_vop987, __mv_vop988, __mv_vop1870, __mv_vop1871,
      __mv_vop992, __mv_vop990, __mv_vop991, __mv_vop995, __mv_vop993,
      __mv_vop994, __mv_vop1872, __mv_vop1873, __mv_vop998, __mv_vop996,
      __mv_vop997, __mv_vop1001, __mv_vop999, __mv_vop1000, __mv_vop1874,
      __mv_vop1875, __mv_vop1004, __mv_vop1002, __mv_vop1003, __mv_vop1007,
      __mv_vop1005, __mv_vop1006, __mv_vop1876, __mv_vop1877, __mv_vop1010,
      __mv_vop1008, __mv_vop1009, __mv_vop1013, __mv_vop1011, __mv_vop1012,
      __mv_vop1878, __mv_vop1879, __mv_vop1016, __mv_vop1014, __mv_vop1015,
      __mv_vop1019, __mv_vop1017, __mv_vop1018, __mv_vop1880, __mv_vop1881,
      __mv_vop1022, __mv_vop1020, __mv_vop1021, __mv_vop1025, __mv_vop1023,
      __mv_vop1024, __mv_vop1882, __mv_vop1883, __mv_vop1028, __mv_vop1026,
      __mv_vop1027, __mv_vop1031, __mv_vop1029, __mv_vop1030, __mv_vop1884,
      __mv_vop1885, __mv_vop1034, __mv_vop1032, __mv_vop1033, __mv_vop1037,
      __mv_vop1035, __mv_vop1036, __mv_vop1886, __mv_vop1887, __mv_vop1040,
      __mv_vop1038, __mv_vop1039, __mv_vop1043, __mv_vop1041, __mv_vop1042,
      __mv_vop1888, __mv_vop1889, __mv_vop1046, __mv_vop1044, __mv_vop1045,
      __mv_vop1049, __mv_vop1047, __mv_vop1048, __mv_vop1890, __mv_vop1891,
      __mv_vop1052, __mv_vop1050, __mv_vop1051, __mv_vop1055, __mv_vop1053,
      __mv_vop1054, __mv_vop1892, __mv_vop1893, __mv_vop1058, __mv_vop1056,
      __mv_vop1057, __mv_vop1061, __mv_vop1059, __mv_vop1060, __mv_vop1894,
      __mv_vop1895, __mv_vop1064, __mv_vop1062, __mv_vop1063, __mv_vop1067,
      __mv_vop1065, __mv_vop1066, __mv_vop1896, __mv_vop1897, __mv_vop1070,
      __mv_vop1068, __mv_vop1069, __mv_vop1073, __mv_vop1071, __mv_vop1072,
      __mv_vop1898, __mv_vop1899, __mv_vop1076, __mv_vop1074, __mv_vop1075,
      __mv_vop1079, __mv_vop1077, __mv_vop1078, __mv_vop1900, __mv_vop1901,
      __mv_vop1082, __mv_vop1080, __mv_vop1081, __mv_vop1085, __mv_vop1083,
      __mv_vop1084, __mv_vop1902, __mv_vop1903, __mv_vop1088, __mv_vop1086,
      __mv_vop1087, __mv_vop1091, __mv_vop1089, __mv_vop1090, __mv_vop1904,
      __mv_vop1905, __mv_vop1094, __mv_vop1092, __mv_vop1093, __mv_vop1097,
      __mv_vop1095, __mv_vop1096, __mv_vop1906, __mv_vop1907, __mv_vop1100,
      __mv_vop1098, __mv_vop1099, __mv_vop1103, __mv_vop1101, __mv_vop1102,
      __mv_vop1908, __mv_vop1909, __mv_vop1106, __mv_vop1104, __mv_vop1105,
      __mv_vop1109, __mv_vop1107, __mv_vop1108, __mv_vop1910, __mv_vop1911,
      __mv_vop1112, __mv_vop1110, __mv_vop1111, __mv_vop1115, __mv_vop1113,
      __mv_vop1114, __mv_vop1912, __mv_vop1913, __mv_vop1118, __mv_vop1116,
      __mv_vop1117, __mv_vop1121, __mv_vop1119, __mv_vop1120, __mv_vop1914,
      __mv_vop1915, __mv_vop1124, __mv_vop1122, __mv_vop1123, __mv_vop1127,
      __mv_vop1125, __mv_vop1126, __mv_vop1916, __mv_vop1917, __mv_vop1130,
      __mv_vop1128, __mv_vop1129, __mv_vop1133, __mv_vop1131, __mv_vop1132,
      __mv_vop1918, __mv_vop1919, __mv_vop1136, __mv_vop1134, __mv_vop1135,
      __mv_vop1139, __mv_vop1137, __mv_vop1138, __mv_vop1920, __mv_vop1921,
      __mv_vop1142, __mv_vop1140, __mv_vop1141, __mv_vop1145, __mv_vop1143,
      __mv_vop1144, __mv_vop1922, __mv_vop1923, __mv_vop1148, __mv_vop1146,
      __mv_vop1147, __mv_vop1151, __mv_vop1149, __mv_vop1150, __mv_vop1924,
      __mv_vop1925, __mv_vop1154, __mv_vop1152, __mv_vop1153, __mv_vop1157,
      __mv_vop1155, __mv_vop1156, __mv_vop1926, __mv_vop1927, __mv_vop1160,
      __mv_vop1158, __mv_vop1159, __mv_vop1163, __mv_vop1161, __mv_vop1162,
      __mv_vop1928, __mv_vop1929, __mv_vop1166, __mv_vop1164, __mv_vop1165,
      __mv_vop1169, __mv_vop1167, __mv_vop1168, __mv_vop1930, __mv_vop1931,
      __mv_vop1172, __mv_vop1170, __mv_vop1171, __mv_vop1175, __mv_vop1173,
      __mv_vop1174, __mv_vop1932, __mv_vop1933, __mv_vop1178, __mv_vop1176,
      __mv_vop1177, __mv_vop1181, __mv_vop1179, __mv_vop1180, __mv_vop1934,
      __mv_vop1935, __mv_vop1184, __mv_vop1182, __mv_vop1183, __mv_vop1187,
      __mv_vop1185, __mv_vop1186, __mv_vop1936, __mv_vop1937, __mv_vop1190,
      __mv_vop1188, __mv_vop1189, __mv_vop1193, __mv_vop1191, __mv_vop1192,
      __mv_vop1938, __mv_vop1939, __mv_vop1196, __mv_vop1194, __mv_vop1195,
      __mv_vop1199, __mv_vop1197, __mv_vop1198, __mv_vop1940, __mv_vop1941,
      __mv_vop1202, __mv_vop1200, __mv_vop1201, __mv_vop1205, __mv_vop1203,
      __mv_vop1204, __mv_vop1942, __mv_vop1943, __mv_vop1208, __mv_vop1206,
      __mv_vop1207, __mv_vop1211, __mv_vop1209, __mv_vop1210, __mv_vop1944,
      __mv_vop1945, __mv_vop1214, __mv_vop1212, __mv_vop1213, __mv_vop1217,
      __mv_vop1215, __mv_vop1216, __mv_vop1946, __mv_vop1947, __mv_vop1220,
      __mv_vop1218, __mv_vop1219, __mv_vop1223, __mv_vop1221, __mv_vop1222,
      __mv_vop1948, __mv_vop1949, __mv_vop1226, __mv_vop1224, __mv_vop1225,
      __mv_vop1229, __mv_vop1227, __mv_vop1228, __mv_vop1950, __mv_vop1951,
      __mv_vop1232, __mv_vop1230, __mv_vop1231, __mv_vop1235, __mv_vop1233,
      __mv_vop1234, __mv_vop1952, __mv_vop1953, __mv_vop1238, __mv_vop1236,
      __mv_vop1237, __mv_vop1241, __mv_vop1239, __mv_vop1240, __mv_vop1954,
      __mv_vop1955, __mv_vop1244, __mv_vop1242, __mv_vop1243, __mv_vop1247,
      __mv_vop1245, __mv_vop1246, __mv_vop1956, __mv_vop1957, __mv_vop1250,
      __mv_vop1248, __mv_vop1249, __mv_vop1253, __mv_vop1251, __mv_vop1252,
      __mv_vop1958, __mv_vop1959, __mv_vop1256, __mv_vop1254, __mv_vop1255,
      __mv_vop1259, __mv_vop1257, __mv_vop1258, __mv_vop1960, __mv_vop1961,
      __mv_vop1262, __mv_vop1260, __mv_vop1261, __mv_vop1265, __mv_vop1263,
      __mv_vop1264, __mv_vop1962, __mv_vop1963, __mv_vop1268, __mv_vop1266,
      __mv_vop1267, __mv_vop1271, __mv_vop1269, __mv_vop1270, __mv_vop1964,
      __mv_vop1965, __mv_vop1274, __mv_vop1272, __mv_vop1273, __mv_vop1277,
      __mv_vop1275, __mv_vop1276, __mv_vop1966, __mv_vop1967, __mv_vop1280,
      __mv_vop1278, __mv_vop1279, __mv_vop1283, __mv_vop1281, __mv_vop1282,
      __mv_vop1968, __mv_vop1969, __mv_vop1286, __mv_vop1284, __mv_vop1285,
      __mv_vop1289, __mv_vop1287, __mv_vop1288, __mv_vop1970, __mv_vop1971,
      __mv_vop1292, __mv_vop1290, __mv_vop1291, __mv_vop1295, __mv_vop1293,
      __mv_vop1294, __mv_vop1972, __mv_vop1973, __mv_vop1298, __mv_vop1296,
      __mv_vop1297, __mv_vop1301, __mv_vop1299, __mv_vop1300, __mv_vop1974,
      __mv_vop1975, __mv_vop1304, __mv_vop1302, __mv_vop1303, __mv_vop1307,
      __mv_vop1305, __mv_vop1306, __mv_vop1976, __mv_vop1977, __mv_vop1310,
      __mv_vop1308, __mv_vop1309, __mv_vop1313, __mv_vop1311, __mv_vop1312,
      __mv_vop1978, __mv_vop1979, __mv_vop1316, __mv_vop1314, __mv_vop1315,
      __mv_vop1319, __mv_vop1317, __mv_vop1318, __mv_vop1980, __mv_vop1981,
      __mv_vop1322, __mv_vop1320, __mv_vop1321, __mv_vop1325, __mv_vop1323,
      __mv_vop1324, __mv_vop1982, __mv_vop1983, __mv_vop1328, __mv_vop1326,
      __mv_vop1327, __mv_vop1331, __mv_vop1329, __mv_vop1330, __mv_vop1984,
      __mv_vop1985, __mv_vop1334, __mv_vop1332, __mv_vop1333, __mv_vop1337,
      __mv_vop1335, __mv_vop1336, __mv_vop1986, __mv_vop1987, __mv_vop1340,
      __mv_vop1338, __mv_vop1339, __mv_vop1343, __mv_vop1341, __mv_vop1342,
      __mv_vop1988, __mv_vop1989, __mv_vop1346, __mv_vop1344, __mv_vop1345,
      __mv_vop1349, __mv_vop1347, __mv_vop1348, __mv_vop1990, __mv_vop1991,
      __mv_vop1352, __mv_vop1350, __mv_vop1351, __mv_vop1355, __mv_vop1353,
      __mv_vop1354, __mv_vop1992, __mv_vop1993, __mv_vop1358, __mv_vop1356,
      __mv_vop1357, __mv_vop1361, __mv_vop1359, __mv_vop1360, __mv_vop1994,
      __mv_vop1995, __mv_vop1364, __mv_vop1362, __mv_vop1363, __mv_vop1367,
      __mv_vop1365, __mv_vop1366, __mv_vop1996, __mv_vop1997, __mv_vop1370,
      __mv_vop1368, __mv_vop1369, __mv_vop1373, __mv_vop1371, __mv_vop1372,
      __mv_vop1998, __mv_vop1999, __mv_vop1376, __mv_vop1374, __mv_vop1375,
      __mv_vop1379, __mv_vop1377, __mv_vop1378, __mv_vop2000, __mv_vop2001,
      __mv_vop1382, __mv_vop1380, __mv_vop1381, __mv_vop1385, __mv_vop1383,
      __mv_vop1384, __mv_vop2002, __mv_vop2003, __mv_vop1388, __mv_vop1386,
      __mv_vop1387, __mv_vop1391, __mv_vop1389, __mv_vop1390, __mv_vop2004,
      __mv_vop2005, __mv_vop1394, __mv_vop1392, __mv_vop1393, __mv_vop1397,
      __mv_vop1395, __mv_vop1396, __mv_vop2006, __mv_vop2007, __mv_vop1400,
      __mv_vop1398, __mv_vop1399, __mv_vop1403, __mv_vop1401, __mv_vop1402,
      __mv_vop2008, __mv_vop2009, __mv_vop1406, __mv_vop1404, __mv_vop1405,
      __mv_vop1409, __mv_vop1407, __mv_vop1408, __mv_vop2010, __mv_vop2011,
      __mv_vop1412, __mv_vop1410, __mv_vop1411, __mv_vop1415, __mv_vop1413,
      __mv_vop1414, __mv_vop2012, __mv_vop2013, __mv_vop1418, __mv_vop1416,
      __mv_vop1417, __mv_vop1421, __mv_vop1419, __mv_vop1420, __mv_vop2014,
      __mv_vop2015, __mv_vop1424, __mv_vop1422, __mv_vop1423, __mv_vop1427,
      __mv_vop1425, __mv_vop1426, __mv_vop2016, __mv_vop2017, __mv_vop1430,
      __mv_vop1428, __mv_vop1429, __mv_vop1433, __mv_vop1431, __mv_vop1432,
      __mv_vop2018, __mv_vop2019, __mv_vop1436, __mv_vop1434, __mv_vop1435,
      __mv_vop1439, __mv_vop1437, __mv_vop1438, __mv_vop2020, __mv_vop2021,
      __mv_vop1442, __mv_vop1440, __mv_vop1441, __mv_vop1445, __mv_vop1443,
      __mv_vop1444, __mv_vop2022, __mv_vop2023, __mv_vop1448, __mv_vop1446,
      __mv_vop1447, __mv_vop1451, __mv_vop1449, __mv_vop1450, __mv_vop2024,
      __mv_vop2025, __mv_vop1454, __mv_vop1452, __mv_vop1453, __mv_vop1457,
      __mv_vop1455, __mv_vop1456, __mv_vop2026, __mv_vop2027, __mv_vop1460,
      __mv_vop1458, __mv_vop1459, __mv_vop1463, __mv_vop1461, __mv_vop1462,
      __mv_vop2028, __mv_vop2029, __mv_vop1466, __mv_vop1464, __mv_vop1465,
      __mv_vop1469, __mv_vop1467, __mv_vop1468, __mv_vop2030, __mv_vop2031,
      __mv_vop1472, __mv_vop1470, __mv_vop1471, __mv_vop1475, __mv_vop1473,
      __mv_vop1474, __mv_vop2032, __mv_vop2033, __mv_vop1478, __mv_vop1476,
      __mv_vop1477, __mv_vop1481, __mv_vop1479, __mv_vop1480, __mv_vop2034,
      __mv_vop2035, __mv_vop1484, __mv_vop1482, __mv_vop1483, __mv_vop1487,
      __mv_vop1485, __mv_vop1486, __mv_vop2036, __mv_vop2037, __mv_vop1490,
      __mv_vop1488, __mv_vop1489, __mv_vop1493, __mv_vop1491, __mv_vop1492,
      __mv_vop2038, __mv_vop2039, __mv_vop1496, __mv_vop1494, __mv_vop1495,
      __mv_vop1499, __mv_vop1497, __mv_vop1498, __mv_vop2040, __mv_vop2041,
      __mv_vop1502, __mv_vop1500, __mv_vop1501, __mv_vop1505, __mv_vop1503,
      __mv_vop1504, __mv_vop2042, __mv_vop2043, __mv_vop1508, __mv_vop1506,
      __mv_vop1507, __mv_vop1511, __mv_vop1509, __mv_vop1510, __mv_vop2044,
      __mv_vop2045, __mv_vop1514, __mv_vop1512, __mv_vop1513, __mv_vop1517,
      __mv_vop1515, __mv_vop1516, __mv_vop2046, __mv_vop2047, __mv_vop1520,
      __mv_vop1518, __mv_vop1519, __mv_vop1523, __mv_vop1521, __mv_vop1522,
      __mv_vop2048, __mv_vop2049, __mv_vop1526, __mv_vop1524, __mv_vop1525,
      __mv_vop1529, __mv_vop1527, __mv_vop1528, __mv_vop2050, __mv_vop2051,
      __mv_vop1532, __mv_vop1530, __mv_vop1531, __mv_vop1535, __mv_vop1533,
      __mv_vop1534, __mv_vop2052, __mv_vop2053, __mv_vop1538, __mv_vop1536,
      __mv_vop1537, __mv_vop1541, __mv_vop1539, __mv_vop1540, __mv_vop2054,
      __mv_vop2055;
  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop0 = _mm256_loadu_pd(&A[(i0 + 0)]);
    __mv_vop1 = _mm256_loadu_pd(&x[((i0 + 0) + 5)]);
    __mv_vop3 = _mm256_loadu_pd(&A[(i0 + 4)]);
    __mv_vop4 = _mm256_loadu_pd(&x[((i0 + 4) + 5)]);
    __mv_vop1542 = _mm256_loadu_pd(&y[((i0 + 0) + 5)]);
    __mv_vop1542 = _mm256_fmadd_pd(__mv_vop0, __mv_vop1, __mv_vop1542);
    _mm256_storeu_pd(&y[((i0 + 0) + 5)], __mv_vop1542);
    __mv_vop1543 = _mm256_loadu_pd(&y[((i0 + 4) + 5)]);
    __mv_vop1543 = _mm256_fmadd_pd(__mv_vop3, __mv_vop4, __mv_vop1543);
    _mm256_storeu_pd(&y[((i0 + 4) + 5)], __mv_vop1543);
    // y[1 * i0 + 5] += A[i0 + 0] * x[1 * i0 + 5];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 5] += A[i0 + 0] * x[1 * i0 + 5];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop6 = _mm256_loadu_pd(&A[((i0 + 0) + 8)]);
    __mv_vop7 = _mm256_loadu_pd(&x[((i0 + 0) + 15)]);
    __mv_vop9 = _mm256_loadu_pd(&A[((i0 + 4) + 8)]);
    __mv_vop10 = _mm256_loadu_pd(&x[((i0 + 4) + 15)]);
    __mv_vop1544 = _mm256_loadu_pd(&y[((i0 + 0) + 14)]);
    __mv_vop1544 = _mm256_fmadd_pd(__mv_vop6, __mv_vop7, __mv_vop1544);
    _mm256_storeu_pd(&y[((i0 + 0) + 14)], __mv_vop1544);
    __mv_vop1545 = _mm256_loadu_pd(&y[((i0 + 4) + 14)]);
    __mv_vop1545 = _mm256_fmadd_pd(__mv_vop9, __mv_vop10, __mv_vop1545);
    _mm256_storeu_pd(&y[((i0 + 4) + 14)], __mv_vop1545);
    // y[1 * i0 + 14] += A[i0 + 8] * x[1 * i0 + 15];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 14] += A[i0 + 8] * x[1 * i0 + 15];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop12 = _mm256_loadu_pd(&A[((i0 + 0) + 16)]);
    __mv_vop13 = _mm256_loadu_pd(&x[((i0 + 0) + 14)]);
    __mv_vop15 = _mm256_loadu_pd(&A[((i0 + 4) + 16)]);
    __mv_vop16 = _mm256_loadu_pd(&x[((i0 + 4) + 14)]);
    __mv_vop1546 = _mm256_loadu_pd(&y[((i0 + 0) + 15)]);
    __mv_vop1546 = _mm256_fmadd_pd(__mv_vop12, __mv_vop13, __mv_vop1546);
    _mm256_storeu_pd(&y[((i0 + 0) + 15)], __mv_vop1546);
    __mv_vop1547 = _mm256_loadu_pd(&y[((i0 + 4) + 15)]);
    __mv_vop1547 = _mm256_fmadd_pd(__mv_vop15, __mv_vop16, __mv_vop1547);
    _mm256_storeu_pd(&y[((i0 + 4) + 15)], __mv_vop1547);
    // y[1 * i0 + 15] += A[i0 + 16] * x[1 * i0 + 14];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 15] += A[i0 + 16] * x[1 * i0 + 14];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop18 = _mm256_loadu_pd(&A[((i0 + 0) + 24)]);
    __mv_vop19 = _mm256_loadu_pd(&x[((i0 + 0) + 23)]);
    __mv_vop21 = _mm256_loadu_pd(&A[((i0 + 4) + 24)]);
    __mv_vop22 = _mm256_loadu_pd(&x[((i0 + 4) + 23)]);
    __mv_vop1548 = _mm256_loadu_pd(&y[((i0 + 0) + 22)]);
    __mv_vop1548 = _mm256_fmadd_pd(__mv_vop18, __mv_vop19, __mv_vop1548);
    _mm256_storeu_pd(&y[((i0 + 0) + 22)], __mv_vop1548);
    __mv_vop1549 = _mm256_loadu_pd(&y[((i0 + 4) + 22)]);
    __mv_vop1549 = _mm256_fmadd_pd(__mv_vop21, __mv_vop22, __mv_vop1549);
    _mm256_storeu_pd(&y[((i0 + 4) + 22)], __mv_vop1549);
    // y[1 * i0 + 22] += A[i0 + 24] * x[1 * i0 + 23];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 22] += A[i0 + 24] * x[1 * i0 + 23];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop24 = _mm256_loadu_pd(&A[((i0 + 0) + 32)]);
    __mv_vop25 = _mm256_loadu_pd(&x[((i0 + 0) + 22)]);
    __mv_vop27 = _mm256_loadu_pd(&A[((i0 + 4) + 32)]);
    __mv_vop28 = _mm256_loadu_pd(&x[((i0 + 4) + 22)]);
    __mv_vop1550 = _mm256_loadu_pd(&y[((i0 + 0) + 23)]);
    __mv_vop1550 = _mm256_fmadd_pd(__mv_vop24, __mv_vop25, __mv_vop1550);
    _mm256_storeu_pd(&y[((i0 + 0) + 23)], __mv_vop1550);
    __mv_vop1551 = _mm256_loadu_pd(&y[((i0 + 4) + 23)]);
    __mv_vop1551 = _mm256_fmadd_pd(__mv_vop27, __mv_vop28, __mv_vop1551);
    _mm256_storeu_pd(&y[((i0 + 4) + 23)], __mv_vop1551);
    // y[1 * i0 + 23] += A[i0 + 32] * x[1 * i0 + 22];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 23] += A[i0 + 32] * x[1 * i0 + 22];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop30 = _mm256_loadu_pd(&A[((i0 + 0) + 40)]);
    __mv_vop31 = _mm256_loadu_pd(&x[((i0 + 0) + 31)]);
    __mv_vop33 = _mm256_loadu_pd(&A[((i0 + 4) + 40)]);
    __mv_vop34 = _mm256_loadu_pd(&x[((i0 + 4) + 31)]);
    __mv_vop1552 = _mm256_loadu_pd(&y[((i0 + 0) + 30)]);
    __mv_vop1552 = _mm256_fmadd_pd(__mv_vop30, __mv_vop31, __mv_vop1552);
    _mm256_storeu_pd(&y[((i0 + 0) + 30)], __mv_vop1552);
    __mv_vop1553 = _mm256_loadu_pd(&y[((i0 + 4) + 30)]);
    __mv_vop1553 = _mm256_fmadd_pd(__mv_vop33, __mv_vop34, __mv_vop1553);
    _mm256_storeu_pd(&y[((i0 + 4) + 30)], __mv_vop1553);
    // y[1 * i0 + 30] += A[i0 + 40] * x[1 * i0 + 31];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 30] += A[i0 + 40] * x[1 * i0 + 31];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop36 = _mm256_loadu_pd(&A[((i0 + 0) + 48)]);
    __mv_vop37 = _mm256_loadu_pd(&x[((i0 + 0) + 30)]);
    __mv_vop39 = _mm256_loadu_pd(&A[((i0 + 4) + 48)]);
    __mv_vop40 = _mm256_loadu_pd(&x[((i0 + 4) + 30)]);
    __mv_vop1554 = _mm256_loadu_pd(&y[((i0 + 0) + 31)]);
    __mv_vop1554 = _mm256_fmadd_pd(__mv_vop36, __mv_vop37, __mv_vop1554);
    _mm256_storeu_pd(&y[((i0 + 0) + 31)], __mv_vop1554);
    __mv_vop1555 = _mm256_loadu_pd(&y[((i0 + 4) + 31)]);
    __mv_vop1555 = _mm256_fmadd_pd(__mv_vop39, __mv_vop40, __mv_vop1555);
    _mm256_storeu_pd(&y[((i0 + 4) + 31)], __mv_vop1555);
    // y[1 * i0 + 31] += A[i0 + 48] * x[1 * i0 + 30];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 31] += A[i0 + 48] * x[1 * i0 + 30];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop42 = _mm256_loadu_pd(&A[((i0 + 0) + 56)]);
    __mv_vop43 = _mm256_loadu_pd(&x[((i0 + 0) + 39)]);
    __mv_vop45 = _mm256_loadu_pd(&A[((i0 + 4) + 56)]);
    __mv_vop46 = _mm256_loadu_pd(&x[((i0 + 4) + 39)]);
    __mv_vop1556 = _mm256_loadu_pd(&y[((i0 + 0) + 38)]);
    __mv_vop1556 = _mm256_fmadd_pd(__mv_vop42, __mv_vop43, __mv_vop1556);
    _mm256_storeu_pd(&y[((i0 + 0) + 38)], __mv_vop1556);
    __mv_vop1557 = _mm256_loadu_pd(&y[((i0 + 4) + 38)]);
    __mv_vop1557 = _mm256_fmadd_pd(__mv_vop45, __mv_vop46, __mv_vop1557);
    _mm256_storeu_pd(&y[((i0 + 4) + 38)], __mv_vop1557);
    // y[1 * i0 + 38] += A[i0 + 56] * x[1 * i0 + 39];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 38] += A[i0 + 56] * x[1 * i0 + 39];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop48 = _mm256_loadu_pd(&A[((i0 + 0) + 64)]);
    __mv_vop49 = _mm256_loadu_pd(&x[((i0 + 0) + 38)]);
    __mv_vop51 = _mm256_loadu_pd(&A[((i0 + 4) + 64)]);
    __mv_vop52 = _mm256_loadu_pd(&x[((i0 + 4) + 38)]);
    __mv_vop1558 = _mm256_loadu_pd(&y[((i0 + 0) + 39)]);
    __mv_vop1558 = _mm256_fmadd_pd(__mv_vop48, __mv_vop49, __mv_vop1558);
    _mm256_storeu_pd(&y[((i0 + 0) + 39)], __mv_vop1558);
    __mv_vop1559 = _mm256_loadu_pd(&y[((i0 + 4) + 39)]);
    __mv_vop1559 = _mm256_fmadd_pd(__mv_vop51, __mv_vop52, __mv_vop1559);
    _mm256_storeu_pd(&y[((i0 + 4) + 39)], __mv_vop1559);
    // y[1 * i0 + 39] += A[i0 + 64] * x[1 * i0 + 38];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 39] += A[i0 + 64] * x[1 * i0 + 38];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop54 = _mm256_loadu_pd(&A[((i0 + 0) + 72)]);
    __mv_vop55 = _mm256_loadu_pd(&x[((i0 + 0) + 47)]);
    __mv_vop57 = _mm256_loadu_pd(&A[((i0 + 4) + 72)]);
    __mv_vop58 = _mm256_loadu_pd(&x[((i0 + 4) + 47)]);
    __mv_vop1560 = _mm256_loadu_pd(&y[((i0 + 0) + 46)]);
    __mv_vop1560 = _mm256_fmadd_pd(__mv_vop54, __mv_vop55, __mv_vop1560);
    _mm256_storeu_pd(&y[((i0 + 0) + 46)], __mv_vop1560);
    __mv_vop1561 = _mm256_loadu_pd(&y[((i0 + 4) + 46)]);
    __mv_vop1561 = _mm256_fmadd_pd(__mv_vop57, __mv_vop58, __mv_vop1561);
    _mm256_storeu_pd(&y[((i0 + 4) + 46)], __mv_vop1561);
    // y[1 * i0 + 46] += A[i0 + 72] * x[1 * i0 + 47];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 46] += A[i0 + 72] * x[1 * i0 + 47];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop60 = _mm256_loadu_pd(&A[((i0 + 0) + 80)]);
    __mv_vop61 = _mm256_loadu_pd(&x[((i0 + 0) + 46)]);
    __mv_vop63 = _mm256_loadu_pd(&A[((i0 + 4) + 80)]);
    __mv_vop64 = _mm256_loadu_pd(&x[((i0 + 4) + 46)]);
    __mv_vop1562 = _mm256_loadu_pd(&y[((i0 + 0) + 47)]);
    __mv_vop1562 = _mm256_fmadd_pd(__mv_vop60, __mv_vop61, __mv_vop1562);
    _mm256_storeu_pd(&y[((i0 + 0) + 47)], __mv_vop1562);
    __mv_vop1563 = _mm256_loadu_pd(&y[((i0 + 4) + 47)]);
    __mv_vop1563 = _mm256_fmadd_pd(__mv_vop63, __mv_vop64, __mv_vop1563);
    _mm256_storeu_pd(&y[((i0 + 4) + 47)], __mv_vop1563);
    // y[1 * i0 + 47] += A[i0 + 80] * x[1 * i0 + 46];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 47] += A[i0 + 80] * x[1 * i0 + 46];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop66 = _mm256_loadu_pd(&A[((i0 + 0) + 88)]);
    __mv_vop67 = _mm256_loadu_pd(&x[((i0 + 0) + 55)]);
    __mv_vop69 = _mm256_loadu_pd(&A[((i0 + 4) + 88)]);
    __mv_vop70 = _mm256_loadu_pd(&x[((i0 + 4) + 55)]);
    __mv_vop1564 = _mm256_loadu_pd(&y[((i0 + 0) + 54)]);
    __mv_vop1564 = _mm256_fmadd_pd(__mv_vop66, __mv_vop67, __mv_vop1564);
    _mm256_storeu_pd(&y[((i0 + 0) + 54)], __mv_vop1564);
    __mv_vop1565 = _mm256_loadu_pd(&y[((i0 + 4) + 54)]);
    __mv_vop1565 = _mm256_fmadd_pd(__mv_vop69, __mv_vop70, __mv_vop1565);
    _mm256_storeu_pd(&y[((i0 + 4) + 54)], __mv_vop1565);
    // y[1 * i0 + 54] += A[i0 + 88] * x[1 * i0 + 55];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 54] += A[i0 + 88] * x[1 * i0 + 55];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop72 = _mm256_loadu_pd(&A[((i0 + 0) + 96)]);
    __mv_vop73 = _mm256_loadu_pd(&x[((i0 + 0) + 54)]);
    __mv_vop75 = _mm256_loadu_pd(&A[((i0 + 4) + 96)]);
    __mv_vop76 = _mm256_loadu_pd(&x[((i0 + 4) + 54)]);
    __mv_vop1566 = _mm256_loadu_pd(&y[((i0 + 0) + 55)]);
    __mv_vop1566 = _mm256_fmadd_pd(__mv_vop72, __mv_vop73, __mv_vop1566);
    _mm256_storeu_pd(&y[((i0 + 0) + 55)], __mv_vop1566);
    __mv_vop1567 = _mm256_loadu_pd(&y[((i0 + 4) + 55)]);
    __mv_vop1567 = _mm256_fmadd_pd(__mv_vop75, __mv_vop76, __mv_vop1567);
    _mm256_storeu_pd(&y[((i0 + 4) + 55)], __mv_vop1567);
    // y[1 * i0 + 55] += A[i0 + 96] * x[1 * i0 + 54];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 55] += A[i0 + 96] * x[1 * i0 + 54];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop78 = _mm256_loadu_pd(&A[((i0 + 0) + 104)]);
    __mv_vop79 = _mm256_loadu_pd(&x[((i0 + 0) + 63)]);
    __mv_vop81 = _mm256_loadu_pd(&A[((i0 + 4) + 104)]);
    __mv_vop82 = _mm256_loadu_pd(&x[((i0 + 4) + 63)]);
    __mv_vop1568 = _mm256_loadu_pd(&y[((i0 + 0) + 62)]);
    __mv_vop1568 = _mm256_fmadd_pd(__mv_vop78, __mv_vop79, __mv_vop1568);
    _mm256_storeu_pd(&y[((i0 + 0) + 62)], __mv_vop1568);
    __mv_vop1569 = _mm256_loadu_pd(&y[((i0 + 4) + 62)]);
    __mv_vop1569 = _mm256_fmadd_pd(__mv_vop81, __mv_vop82, __mv_vop1569);
    _mm256_storeu_pd(&y[((i0 + 4) + 62)], __mv_vop1569);
    // y[1 * i0 + 62] += A[i0 + 104] * x[1 * i0 + 63];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 62] += A[i0 + 104] * x[1 * i0 + 63];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop84 = _mm256_loadu_pd(&A[((i0 + 0) + 112)]);
    __mv_vop85 = _mm256_loadu_pd(&x[((i0 + 0) + 62)]);
    __mv_vop87 = _mm256_loadu_pd(&A[((i0 + 4) + 112)]);
    __mv_vop88 = _mm256_loadu_pd(&x[((i0 + 4) + 62)]);
    __mv_vop1570 = _mm256_loadu_pd(&y[((i0 + 0) + 63)]);
    __mv_vop1570 = _mm256_fmadd_pd(__mv_vop84, __mv_vop85, __mv_vop1570);
    _mm256_storeu_pd(&y[((i0 + 0) + 63)], __mv_vop1570);
    __mv_vop1571 = _mm256_loadu_pd(&y[((i0 + 4) + 63)]);
    __mv_vop1571 = _mm256_fmadd_pd(__mv_vop87, __mv_vop88, __mv_vop1571);
    _mm256_storeu_pd(&y[((i0 + 4) + 63)], __mv_vop1571);
    // y[1 * i0 + 63] += A[i0 + 112] * x[1 * i0 + 62];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 63] += A[i0 + 112] * x[1 * i0 + 62];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop90 = _mm256_loadu_pd(&A[((i0 + 0) + 120)]);
    __mv_vop91 = _mm256_loadu_pd(&x[((i0 + 0) + 71)]);
    __mv_vop93 = _mm256_loadu_pd(&A[((i0 + 4) + 120)]);
    __mv_vop94 = _mm256_loadu_pd(&x[((i0 + 4) + 71)]);
    __mv_vop1572 = _mm256_loadu_pd(&y[((i0 + 0) + 70)]);
    __mv_vop1572 = _mm256_fmadd_pd(__mv_vop90, __mv_vop91, __mv_vop1572);
    _mm256_storeu_pd(&y[((i0 + 0) + 70)], __mv_vop1572);
    __mv_vop1573 = _mm256_loadu_pd(&y[((i0 + 4) + 70)]);
    __mv_vop1573 = _mm256_fmadd_pd(__mv_vop93, __mv_vop94, __mv_vop1573);
    _mm256_storeu_pd(&y[((i0 + 4) + 70)], __mv_vop1573);
    // y[1 * i0 + 70] += A[i0 + 120] * x[1 * i0 + 71];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 70] += A[i0 + 120] * x[1 * i0 + 71];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop96 = _mm256_loadu_pd(&A[((i0 + 0) + 128)]);
    __mv_vop97 = _mm256_loadu_pd(&x[((i0 + 0) + 70)]);
    __mv_vop99 = _mm256_loadu_pd(&A[((i0 + 4) + 128)]);
    __mv_vop100 = _mm256_loadu_pd(&x[((i0 + 4) + 70)]);
    __mv_vop1574 = _mm256_loadu_pd(&y[((i0 + 0) + 71)]);
    __mv_vop1574 = _mm256_fmadd_pd(__mv_vop96, __mv_vop97, __mv_vop1574);
    _mm256_storeu_pd(&y[((i0 + 0) + 71)], __mv_vop1574);
    __mv_vop1575 = _mm256_loadu_pd(&y[((i0 + 4) + 71)]);
    __mv_vop1575 = _mm256_fmadd_pd(__mv_vop99, __mv_vop100, __mv_vop1575);
    _mm256_storeu_pd(&y[((i0 + 4) + 71)], __mv_vop1575);
    // y[1 * i0 + 71] += A[i0 + 128] * x[1 * i0 + 70];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 71] += A[i0 + 128] * x[1 * i0 + 70];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop102 = _mm256_loadu_pd(&A[((i0 + 0) + 136)]);
    __mv_vop103 = _mm256_loadu_pd(&x[((i0 + 0) + 79)]);
    __mv_vop105 = _mm256_loadu_pd(&A[((i0 + 4) + 136)]);
    __mv_vop106 = _mm256_loadu_pd(&x[((i0 + 4) + 79)]);
    __mv_vop1576 = _mm256_loadu_pd(&y[((i0 + 0) + 78)]);
    __mv_vop1576 = _mm256_fmadd_pd(__mv_vop102, __mv_vop103, __mv_vop1576);
    _mm256_storeu_pd(&y[((i0 + 0) + 78)], __mv_vop1576);
    __mv_vop1577 = _mm256_loadu_pd(&y[((i0 + 4) + 78)]);
    __mv_vop1577 = _mm256_fmadd_pd(__mv_vop105, __mv_vop106, __mv_vop1577);
    _mm256_storeu_pd(&y[((i0 + 4) + 78)], __mv_vop1577);
    // y[1 * i0 + 78] += A[i0 + 136] * x[1 * i0 + 79];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 78] += A[i0 + 136] * x[1 * i0 + 79];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop108 = _mm256_loadu_pd(&A[((i0 + 0) + 144)]);
    __mv_vop109 = _mm256_loadu_pd(&x[((i0 + 0) + 78)]);
    __mv_vop111 = _mm256_loadu_pd(&A[((i0 + 4) + 144)]);
    __mv_vop112 = _mm256_loadu_pd(&x[((i0 + 4) + 78)]);
    __mv_vop1578 = _mm256_loadu_pd(&y[((i0 + 0) + 79)]);
    __mv_vop1578 = _mm256_fmadd_pd(__mv_vop108, __mv_vop109, __mv_vop1578);
    _mm256_storeu_pd(&y[((i0 + 0) + 79)], __mv_vop1578);
    __mv_vop1579 = _mm256_loadu_pd(&y[((i0 + 4) + 79)]);
    __mv_vop1579 = _mm256_fmadd_pd(__mv_vop111, __mv_vop112, __mv_vop1579);
    _mm256_storeu_pd(&y[((i0 + 4) + 79)], __mv_vop1579);
    // y[1 * i0 + 79] += A[i0 + 144] * x[1 * i0 + 78];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 79] += A[i0 + 144] * x[1 * i0 + 78];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop114 = _mm256_loadu_pd(&A[((i0 + 0) + 152)]);
    __mv_vop115 = _mm256_loadu_pd(&x[((i0 + 0) + 87)]);
    __mv_vop117 = _mm256_loadu_pd(&A[((i0 + 4) + 152)]);
    __mv_vop118 = _mm256_loadu_pd(&x[((i0 + 4) + 87)]);
    __mv_vop1580 = _mm256_loadu_pd(&y[((i0 + 0) + 86)]);
    __mv_vop1580 = _mm256_fmadd_pd(__mv_vop114, __mv_vop115, __mv_vop1580);
    _mm256_storeu_pd(&y[((i0 + 0) + 86)], __mv_vop1580);
    __mv_vop1581 = _mm256_loadu_pd(&y[((i0 + 4) + 86)]);
    __mv_vop1581 = _mm256_fmadd_pd(__mv_vop117, __mv_vop118, __mv_vop1581);
    _mm256_storeu_pd(&y[((i0 + 4) + 86)], __mv_vop1581);
    // y[1 * i0 + 86] += A[i0 + 152] * x[1 * i0 + 87];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 86] += A[i0 + 152] * x[1 * i0 + 87];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop120 = _mm256_loadu_pd(&A[((i0 + 0) + 160)]);
    __mv_vop121 = _mm256_loadu_pd(&x[((i0 + 0) + 86)]);
    __mv_vop123 = _mm256_loadu_pd(&A[((i0 + 4) + 160)]);
    __mv_vop124 = _mm256_loadu_pd(&x[((i0 + 4) + 86)]);
    __mv_vop1582 = _mm256_loadu_pd(&y[((i0 + 0) + 87)]);
    __mv_vop1582 = _mm256_fmadd_pd(__mv_vop120, __mv_vop121, __mv_vop1582);
    _mm256_storeu_pd(&y[((i0 + 0) + 87)], __mv_vop1582);
    __mv_vop1583 = _mm256_loadu_pd(&y[((i0 + 4) + 87)]);
    __mv_vop1583 = _mm256_fmadd_pd(__mv_vop123, __mv_vop124, __mv_vop1583);
    _mm256_storeu_pd(&y[((i0 + 4) + 87)], __mv_vop1583);
    // y[1 * i0 + 87] += A[i0 + 160] * x[1 * i0 + 86];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 87] += A[i0 + 160] * x[1 * i0 + 86];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop126 = _mm256_loadu_pd(&A[((i0 + 0) + 168)]);
    __mv_vop127 = _mm256_loadu_pd(&x[((i0 + 0) + 95)]);
    __mv_vop129 = _mm256_loadu_pd(&A[((i0 + 4) + 168)]);
    __mv_vop130 = _mm256_loadu_pd(&x[((i0 + 4) + 95)]);
    __mv_vop1584 = _mm256_loadu_pd(&y[((i0 + 0) + 94)]);
    __mv_vop1584 = _mm256_fmadd_pd(__mv_vop126, __mv_vop127, __mv_vop1584);
    _mm256_storeu_pd(&y[((i0 + 0) + 94)], __mv_vop1584);
    __mv_vop1585 = _mm256_loadu_pd(&y[((i0 + 4) + 94)]);
    __mv_vop1585 = _mm256_fmadd_pd(__mv_vop129, __mv_vop130, __mv_vop1585);
    _mm256_storeu_pd(&y[((i0 + 4) + 94)], __mv_vop1585);
    // y[1 * i0 + 94] += A[i0 + 168] * x[1 * i0 + 95];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 94] += A[i0 + 168] * x[1 * i0 + 95];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop132 = _mm256_loadu_pd(&A[((i0 + 0) + 176)]);
    __mv_vop133 = _mm256_loadu_pd(&x[((i0 + 0) + 94)]);
    __mv_vop135 = _mm256_loadu_pd(&A[((i0 + 4) + 176)]);
    __mv_vop136 = _mm256_loadu_pd(&x[((i0 + 4) + 94)]);
    __mv_vop1586 = _mm256_loadu_pd(&y[((i0 + 0) + 95)]);
    __mv_vop1586 = _mm256_fmadd_pd(__mv_vop132, __mv_vop133, __mv_vop1586);
    _mm256_storeu_pd(&y[((i0 + 0) + 95)], __mv_vop1586);
    __mv_vop1587 = _mm256_loadu_pd(&y[((i0 + 4) + 95)]);
    __mv_vop1587 = _mm256_fmadd_pd(__mv_vop135, __mv_vop136, __mv_vop1587);
    _mm256_storeu_pd(&y[((i0 + 4) + 95)], __mv_vop1587);
    // y[1 * i0 + 95] += A[i0 + 176] * x[1 * i0 + 94];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 95] += A[i0 + 176] * x[1 * i0 + 94];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop138 = _mm256_loadu_pd(&A[((i0 + 0) + 184)]);
    __mv_vop139 = _mm256_loadu_pd(&x[((i0 + 0) + 103)]);
    __mv_vop141 = _mm256_loadu_pd(&A[((i0 + 4) + 184)]);
    __mv_vop142 = _mm256_loadu_pd(&x[((i0 + 4) + 103)]);
    __mv_vop1588 = _mm256_loadu_pd(&y[((i0 + 0) + 102)]);
    __mv_vop1588 = _mm256_fmadd_pd(__mv_vop138, __mv_vop139, __mv_vop1588);
    _mm256_storeu_pd(&y[((i0 + 0) + 102)], __mv_vop1588);
    __mv_vop1589 = _mm256_loadu_pd(&y[((i0 + 4) + 102)]);
    __mv_vop1589 = _mm256_fmadd_pd(__mv_vop141, __mv_vop142, __mv_vop1589);
    _mm256_storeu_pd(&y[((i0 + 4) + 102)], __mv_vop1589);
    // y[1 * i0 + 102] += A[i0 + 184] * x[1 * i0 + 103];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 102] += A[i0 + 184] * x[1 * i0 + 103];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop144 = _mm256_loadu_pd(&A[((i0 + 0) + 192)]);
    __mv_vop145 = _mm256_loadu_pd(&x[((i0 + 0) + 102)]);
    __mv_vop147 = _mm256_loadu_pd(&A[((i0 + 4) + 192)]);
    __mv_vop148 = _mm256_loadu_pd(&x[((i0 + 4) + 102)]);
    __mv_vop1590 = _mm256_loadu_pd(&y[((i0 + 0) + 103)]);
    __mv_vop1590 = _mm256_fmadd_pd(__mv_vop144, __mv_vop145, __mv_vop1590);
    _mm256_storeu_pd(&y[((i0 + 0) + 103)], __mv_vop1590);
    __mv_vop1591 = _mm256_loadu_pd(&y[((i0 + 4) + 103)]);
    __mv_vop1591 = _mm256_fmadd_pd(__mv_vop147, __mv_vop148, __mv_vop1591);
    _mm256_storeu_pd(&y[((i0 + 4) + 103)], __mv_vop1591);
    // y[1 * i0 + 103] += A[i0 + 192] * x[1 * i0 + 102];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 103] += A[i0 + 192] * x[1 * i0 + 102];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop150 = _mm256_loadu_pd(&A[((i0 + 0) + 200)]);
    __mv_vop151 = _mm256_loadu_pd(&x[((i0 + 0) + 111)]);
    __mv_vop153 = _mm256_loadu_pd(&A[((i0 + 4) + 200)]);
    __mv_vop154 = _mm256_loadu_pd(&x[((i0 + 4) + 111)]);
    __mv_vop1592 = _mm256_loadu_pd(&y[((i0 + 0) + 110)]);
    __mv_vop1592 = _mm256_fmadd_pd(__mv_vop150, __mv_vop151, __mv_vop1592);
    _mm256_storeu_pd(&y[((i0 + 0) + 110)], __mv_vop1592);
    __mv_vop1593 = _mm256_loadu_pd(&y[((i0 + 4) + 110)]);
    __mv_vop1593 = _mm256_fmadd_pd(__mv_vop153, __mv_vop154, __mv_vop1593);
    _mm256_storeu_pd(&y[((i0 + 4) + 110)], __mv_vop1593);
    // y[1 * i0 + 110] += A[i0 + 200] * x[1 * i0 + 111];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 110] += A[i0 + 200] * x[1 * i0 + 111];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop156 = _mm256_loadu_pd(&A[((i0 + 0) + 208)]);
    __mv_vop157 = _mm256_loadu_pd(&x[((i0 + 0) + 110)]);
    __mv_vop159 = _mm256_loadu_pd(&A[((i0 + 4) + 208)]);
    __mv_vop160 = _mm256_loadu_pd(&x[((i0 + 4) + 110)]);
    __mv_vop1594 = _mm256_loadu_pd(&y[((i0 + 0) + 111)]);
    __mv_vop1594 = _mm256_fmadd_pd(__mv_vop156, __mv_vop157, __mv_vop1594);
    _mm256_storeu_pd(&y[((i0 + 0) + 111)], __mv_vop1594);
    __mv_vop1595 = _mm256_loadu_pd(&y[((i0 + 4) + 111)]);
    __mv_vop1595 = _mm256_fmadd_pd(__mv_vop159, __mv_vop160, __mv_vop1595);
    _mm256_storeu_pd(&y[((i0 + 4) + 111)], __mv_vop1595);
    // y[1 * i0 + 111] += A[i0 + 208] * x[1 * i0 + 110];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 111] += A[i0 + 208] * x[1 * i0 + 110];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop162 = _mm256_loadu_pd(&A[((i0 + 0) + 216)]);
    __mv_vop163 = _mm256_loadu_pd(&x[((i0 + 0) + 119)]);
    __mv_vop165 = _mm256_loadu_pd(&A[((i0 + 4) + 216)]);
    __mv_vop166 = _mm256_loadu_pd(&x[((i0 + 4) + 119)]);
    __mv_vop1596 = _mm256_loadu_pd(&y[((i0 + 0) + 118)]);
    __mv_vop1596 = _mm256_fmadd_pd(__mv_vop162, __mv_vop163, __mv_vop1596);
    _mm256_storeu_pd(&y[((i0 + 0) + 118)], __mv_vop1596);
    __mv_vop1597 = _mm256_loadu_pd(&y[((i0 + 4) + 118)]);
    __mv_vop1597 = _mm256_fmadd_pd(__mv_vop165, __mv_vop166, __mv_vop1597);
    _mm256_storeu_pd(&y[((i0 + 4) + 118)], __mv_vop1597);
    // y[1 * i0 + 118] += A[i0 + 216] * x[1 * i0 + 119];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 118] += A[i0 + 216] * x[1 * i0 + 119];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop168 = _mm256_loadu_pd(&A[((i0 + 0) + 224)]);
    __mv_vop169 = _mm256_loadu_pd(&x[((i0 + 0) + 118)]);
    __mv_vop171 = _mm256_loadu_pd(&A[((i0 + 4) + 224)]);
    __mv_vop172 = _mm256_loadu_pd(&x[((i0 + 4) + 118)]);
    __mv_vop1598 = _mm256_loadu_pd(&y[((i0 + 0) + 119)]);
    __mv_vop1598 = _mm256_fmadd_pd(__mv_vop168, __mv_vop169, __mv_vop1598);
    _mm256_storeu_pd(&y[((i0 + 0) + 119)], __mv_vop1598);
    __mv_vop1599 = _mm256_loadu_pd(&y[((i0 + 4) + 119)]);
    __mv_vop1599 = _mm256_fmadd_pd(__mv_vop171, __mv_vop172, __mv_vop1599);
    _mm256_storeu_pd(&y[((i0 + 4) + 119)], __mv_vop1599);
    // y[1 * i0 + 119] += A[i0 + 224] * x[1 * i0 + 118];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 119] += A[i0 + 224] * x[1 * i0 + 118];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop174 = _mm256_loadu_pd(&A[((i0 + 0) + 232)]);
    __mv_vop175 = _mm256_loadu_pd(&x[((i0 + 0) + 127)]);
    __mv_vop177 = _mm256_loadu_pd(&A[((i0 + 4) + 232)]);
    __mv_vop178 = _mm256_loadu_pd(&x[((i0 + 4) + 127)]);
    __mv_vop1600 = _mm256_loadu_pd(&y[((i0 + 0) + 126)]);
    __mv_vop1600 = _mm256_fmadd_pd(__mv_vop174, __mv_vop175, __mv_vop1600);
    _mm256_storeu_pd(&y[((i0 + 0) + 126)], __mv_vop1600);
    __mv_vop1601 = _mm256_loadu_pd(&y[((i0 + 4) + 126)]);
    __mv_vop1601 = _mm256_fmadd_pd(__mv_vop177, __mv_vop178, __mv_vop1601);
    _mm256_storeu_pd(&y[((i0 + 4) + 126)], __mv_vop1601);
    // y[1 * i0 + 126] += A[i0 + 232] * x[1 * i0 + 127];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 126] += A[i0 + 232] * x[1 * i0 + 127];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop180 = _mm256_loadu_pd(&A[((i0 + 0) + 240)]);
    __mv_vop181 = _mm256_loadu_pd(&x[((i0 + 0) + 126)]);
    __mv_vop183 = _mm256_loadu_pd(&A[((i0 + 4) + 240)]);
    __mv_vop184 = _mm256_loadu_pd(&x[((i0 + 4) + 126)]);
    __mv_vop1602 = _mm256_loadu_pd(&y[((i0 + 0) + 127)]);
    __mv_vop1602 = _mm256_fmadd_pd(__mv_vop180, __mv_vop181, __mv_vop1602);
    _mm256_storeu_pd(&y[((i0 + 0) + 127)], __mv_vop1602);
    __mv_vop1603 = _mm256_loadu_pd(&y[((i0 + 4) + 127)]);
    __mv_vop1603 = _mm256_fmadd_pd(__mv_vop183, __mv_vop184, __mv_vop1603);
    _mm256_storeu_pd(&y[((i0 + 4) + 127)], __mv_vop1603);
    // y[1 * i0 + 127] += A[i0 + 240] * x[1 * i0 + 126];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 127] += A[i0 + 240] * x[1 * i0 + 126];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop186 = _mm256_loadu_pd(&A[((i0 + 0) + 248)]);
    __mv_vop187 = _mm256_loadu_pd(&x[((i0 + 0) + 135)]);
    __mv_vop189 = _mm256_loadu_pd(&A[((i0 + 4) + 248)]);
    __mv_vop190 = _mm256_loadu_pd(&x[((i0 + 4) + 135)]);
    __mv_vop1604 = _mm256_loadu_pd(&y[((i0 + 0) + 134)]);
    __mv_vop1604 = _mm256_fmadd_pd(__mv_vop186, __mv_vop187, __mv_vop1604);
    _mm256_storeu_pd(&y[((i0 + 0) + 134)], __mv_vop1604);
    __mv_vop1605 = _mm256_loadu_pd(&y[((i0 + 4) + 134)]);
    __mv_vop1605 = _mm256_fmadd_pd(__mv_vop189, __mv_vop190, __mv_vop1605);
    _mm256_storeu_pd(&y[((i0 + 4) + 134)], __mv_vop1605);
    // y[1 * i0 + 134] += A[i0 + 248] * x[1 * i0 + 135];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 134] += A[i0 + 248] * x[1 * i0 + 135];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop192 = _mm256_loadu_pd(&A[((i0 + 0) + 256)]);
    __mv_vop193 = _mm256_loadu_pd(&x[((i0 + 0) + 134)]);
    __mv_vop195 = _mm256_loadu_pd(&A[((i0 + 4) + 256)]);
    __mv_vop196 = _mm256_loadu_pd(&x[((i0 + 4) + 134)]);
    __mv_vop1606 = _mm256_loadu_pd(&y[((i0 + 0) + 135)]);
    __mv_vop1606 = _mm256_fmadd_pd(__mv_vop192, __mv_vop193, __mv_vop1606);
    _mm256_storeu_pd(&y[((i0 + 0) + 135)], __mv_vop1606);
    __mv_vop1607 = _mm256_loadu_pd(&y[((i0 + 4) + 135)]);
    __mv_vop1607 = _mm256_fmadd_pd(__mv_vop195, __mv_vop196, __mv_vop1607);
    _mm256_storeu_pd(&y[((i0 + 4) + 135)], __mv_vop1607);
    // y[1 * i0 + 135] += A[i0 + 256] * x[1 * i0 + 134];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 135] += A[i0 + 256] * x[1 * i0 + 134];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop198 = _mm256_loadu_pd(&A[((i0 + 0) + 264)]);
    __mv_vop199 = _mm256_loadu_pd(&x[((i0 + 0) + 143)]);
    __mv_vop201 = _mm256_loadu_pd(&A[((i0 + 4) + 264)]);
    __mv_vop202 = _mm256_loadu_pd(&x[((i0 + 4) + 143)]);
    __mv_vop1608 = _mm256_loadu_pd(&y[((i0 + 0) + 142)]);
    __mv_vop1608 = _mm256_fmadd_pd(__mv_vop198, __mv_vop199, __mv_vop1608);
    _mm256_storeu_pd(&y[((i0 + 0) + 142)], __mv_vop1608);
    __mv_vop1609 = _mm256_loadu_pd(&y[((i0 + 4) + 142)]);
    __mv_vop1609 = _mm256_fmadd_pd(__mv_vop201, __mv_vop202, __mv_vop1609);
    _mm256_storeu_pd(&y[((i0 + 4) + 142)], __mv_vop1609);
    // y[1 * i0 + 142] += A[i0 + 264] * x[1 * i0 + 143];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 142] += A[i0 + 264] * x[1 * i0 + 143];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop204 = _mm256_loadu_pd(&A[((i0 + 0) + 272)]);
    __mv_vop205 = _mm256_loadu_pd(&x[((i0 + 0) + 142)]);
    __mv_vop207 = _mm256_loadu_pd(&A[((i0 + 4) + 272)]);
    __mv_vop208 = _mm256_loadu_pd(&x[((i0 + 4) + 142)]);
    __mv_vop1610 = _mm256_loadu_pd(&y[((i0 + 0) + 143)]);
    __mv_vop1610 = _mm256_fmadd_pd(__mv_vop204, __mv_vop205, __mv_vop1610);
    _mm256_storeu_pd(&y[((i0 + 0) + 143)], __mv_vop1610);
    __mv_vop1611 = _mm256_loadu_pd(&y[((i0 + 4) + 143)]);
    __mv_vop1611 = _mm256_fmadd_pd(__mv_vop207, __mv_vop208, __mv_vop1611);
    _mm256_storeu_pd(&y[((i0 + 4) + 143)], __mv_vop1611);
    // y[1 * i0 + 143] += A[i0 + 272] * x[1 * i0 + 142];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 143] += A[i0 + 272] * x[1 * i0 + 142];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop210 = _mm256_loadu_pd(&A[((i0 + 0) + 280)]);
    __mv_vop211 = _mm256_loadu_pd(&x[((i0 + 0) + 151)]);
    __mv_vop213 = _mm256_loadu_pd(&A[((i0 + 4) + 280)]);
    __mv_vop214 = _mm256_loadu_pd(&x[((i0 + 4) + 151)]);
    __mv_vop1612 = _mm256_loadu_pd(&y[((i0 + 0) + 150)]);
    __mv_vop1612 = _mm256_fmadd_pd(__mv_vop210, __mv_vop211, __mv_vop1612);
    _mm256_storeu_pd(&y[((i0 + 0) + 150)], __mv_vop1612);
    __mv_vop1613 = _mm256_loadu_pd(&y[((i0 + 4) + 150)]);
    __mv_vop1613 = _mm256_fmadd_pd(__mv_vop213, __mv_vop214, __mv_vop1613);
    _mm256_storeu_pd(&y[((i0 + 4) + 150)], __mv_vop1613);
    // y[1 * i0 + 150] += A[i0 + 280] * x[1 * i0 + 151];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 150] += A[i0 + 280] * x[1 * i0 + 151];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop216 = _mm256_loadu_pd(&A[((i0 + 0) + 288)]);
    __mv_vop217 = _mm256_loadu_pd(&x[((i0 + 0) + 150)]);
    __mv_vop219 = _mm256_loadu_pd(&A[((i0 + 4) + 288)]);
    __mv_vop220 = _mm256_loadu_pd(&x[((i0 + 4) + 150)]);
    __mv_vop1614 = _mm256_loadu_pd(&y[((i0 + 0) + 151)]);
    __mv_vop1614 = _mm256_fmadd_pd(__mv_vop216, __mv_vop217, __mv_vop1614);
    _mm256_storeu_pd(&y[((i0 + 0) + 151)], __mv_vop1614);
    __mv_vop1615 = _mm256_loadu_pd(&y[((i0 + 4) + 151)]);
    __mv_vop1615 = _mm256_fmadd_pd(__mv_vop219, __mv_vop220, __mv_vop1615);
    _mm256_storeu_pd(&y[((i0 + 4) + 151)], __mv_vop1615);
    // y[1 * i0 + 151] += A[i0 + 288] * x[1 * i0 + 150];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 151] += A[i0 + 288] * x[1 * i0 + 150];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop222 = _mm256_loadu_pd(&A[((i0 + 0) + 296)]);
    __mv_vop223 = _mm256_loadu_pd(&x[((i0 + 0) + 159)]);
    __mv_vop225 = _mm256_loadu_pd(&A[((i0 + 4) + 296)]);
    __mv_vop226 = _mm256_loadu_pd(&x[((i0 + 4) + 159)]);
    __mv_vop1616 = _mm256_loadu_pd(&y[((i0 + 0) + 158)]);
    __mv_vop1616 = _mm256_fmadd_pd(__mv_vop222, __mv_vop223, __mv_vop1616);
    _mm256_storeu_pd(&y[((i0 + 0) + 158)], __mv_vop1616);
    __mv_vop1617 = _mm256_loadu_pd(&y[((i0 + 4) + 158)]);
    __mv_vop1617 = _mm256_fmadd_pd(__mv_vop225, __mv_vop226, __mv_vop1617);
    _mm256_storeu_pd(&y[((i0 + 4) + 158)], __mv_vop1617);
    // y[1 * i0 + 158] += A[i0 + 296] * x[1 * i0 + 159];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 158] += A[i0 + 296] * x[1 * i0 + 159];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop228 = _mm256_loadu_pd(&A[((i0 + 0) + 304)]);
    __mv_vop229 = _mm256_loadu_pd(&x[((i0 + 0) + 158)]);
    __mv_vop231 = _mm256_loadu_pd(&A[((i0 + 4) + 304)]);
    __mv_vop232 = _mm256_loadu_pd(&x[((i0 + 4) + 158)]);
    __mv_vop1618 = _mm256_loadu_pd(&y[((i0 + 0) + 159)]);
    __mv_vop1618 = _mm256_fmadd_pd(__mv_vop228, __mv_vop229, __mv_vop1618);
    _mm256_storeu_pd(&y[((i0 + 0) + 159)], __mv_vop1618);
    __mv_vop1619 = _mm256_loadu_pd(&y[((i0 + 4) + 159)]);
    __mv_vop1619 = _mm256_fmadd_pd(__mv_vop231, __mv_vop232, __mv_vop1619);
    _mm256_storeu_pd(&y[((i0 + 4) + 159)], __mv_vop1619);
    // y[1 * i0 + 159] += A[i0 + 304] * x[1 * i0 + 158];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 159] += A[i0 + 304] * x[1 * i0 + 158];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop234 = _mm256_loadu_pd(&A[((i0 + 0) + 312)]);
    __mv_vop235 = _mm256_loadu_pd(&x[((i0 + 0) + 167)]);
    __mv_vop237 = _mm256_loadu_pd(&A[((i0 + 4) + 312)]);
    __mv_vop238 = _mm256_loadu_pd(&x[((i0 + 4) + 167)]);
    __mv_vop1620 = _mm256_loadu_pd(&y[((i0 + 0) + 166)]);
    __mv_vop1620 = _mm256_fmadd_pd(__mv_vop234, __mv_vop235, __mv_vop1620);
    _mm256_storeu_pd(&y[((i0 + 0) + 166)], __mv_vop1620);
    __mv_vop1621 = _mm256_loadu_pd(&y[((i0 + 4) + 166)]);
    __mv_vop1621 = _mm256_fmadd_pd(__mv_vop237, __mv_vop238, __mv_vop1621);
    _mm256_storeu_pd(&y[((i0 + 4) + 166)], __mv_vop1621);
    // y[1 * i0 + 166] += A[i0 + 312] * x[1 * i0 + 167];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 166] += A[i0 + 312] * x[1 * i0 + 167];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop240 = _mm256_loadu_pd(&A[((i0 + 0) + 320)]);
    __mv_vop241 = _mm256_loadu_pd(&x[((i0 + 0) + 166)]);
    __mv_vop243 = _mm256_loadu_pd(&A[((i0 + 4) + 320)]);
    __mv_vop244 = _mm256_loadu_pd(&x[((i0 + 4) + 166)]);
    __mv_vop1622 = _mm256_loadu_pd(&y[((i0 + 0) + 167)]);
    __mv_vop1622 = _mm256_fmadd_pd(__mv_vop240, __mv_vop241, __mv_vop1622);
    _mm256_storeu_pd(&y[((i0 + 0) + 167)], __mv_vop1622);
    __mv_vop1623 = _mm256_loadu_pd(&y[((i0 + 4) + 167)]);
    __mv_vop1623 = _mm256_fmadd_pd(__mv_vop243, __mv_vop244, __mv_vop1623);
    _mm256_storeu_pd(&y[((i0 + 4) + 167)], __mv_vop1623);
    // y[1 * i0 + 167] += A[i0 + 320] * x[1 * i0 + 166];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 167] += A[i0 + 320] * x[1 * i0 + 166];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop246 = _mm256_loadu_pd(&A[((i0 + 0) + 328)]);
    __mv_vop247 = _mm256_loadu_pd(&x[((i0 + 0) + 175)]);
    __mv_vop249 = _mm256_loadu_pd(&A[((i0 + 4) + 328)]);
    __mv_vop250 = _mm256_loadu_pd(&x[((i0 + 4) + 175)]);
    __mv_vop1624 = _mm256_loadu_pd(&y[((i0 + 0) + 174)]);
    __mv_vop1624 = _mm256_fmadd_pd(__mv_vop246, __mv_vop247, __mv_vop1624);
    _mm256_storeu_pd(&y[((i0 + 0) + 174)], __mv_vop1624);
    __mv_vop1625 = _mm256_loadu_pd(&y[((i0 + 4) + 174)]);
    __mv_vop1625 = _mm256_fmadd_pd(__mv_vop249, __mv_vop250, __mv_vop1625);
    _mm256_storeu_pd(&y[((i0 + 4) + 174)], __mv_vop1625);
    // y[1 * i0 + 174] += A[i0 + 328] * x[1 * i0 + 175];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 174] += A[i0 + 328] * x[1 * i0 + 175];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop252 = _mm256_loadu_pd(&A[((i0 + 0) + 336)]);
    __mv_vop253 = _mm256_loadu_pd(&x[((i0 + 0) + 174)]);
    __mv_vop255 = _mm256_loadu_pd(&A[((i0 + 4) + 336)]);
    __mv_vop256 = _mm256_loadu_pd(&x[((i0 + 4) + 174)]);
    __mv_vop1626 = _mm256_loadu_pd(&y[((i0 + 0) + 175)]);
    __mv_vop1626 = _mm256_fmadd_pd(__mv_vop252, __mv_vop253, __mv_vop1626);
    _mm256_storeu_pd(&y[((i0 + 0) + 175)], __mv_vop1626);
    __mv_vop1627 = _mm256_loadu_pd(&y[((i0 + 4) + 175)]);
    __mv_vop1627 = _mm256_fmadd_pd(__mv_vop255, __mv_vop256, __mv_vop1627);
    _mm256_storeu_pd(&y[((i0 + 4) + 175)], __mv_vop1627);
    // y[1 * i0 + 175] += A[i0 + 336] * x[1 * i0 + 174];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 175] += A[i0 + 336] * x[1 * i0 + 174];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop258 = _mm256_loadu_pd(&A[((i0 + 0) + 344)]);
    __mv_vop259 = _mm256_loadu_pd(&x[((i0 + 0) + 183)]);
    __mv_vop261 = _mm256_loadu_pd(&A[((i0 + 4) + 344)]);
    __mv_vop262 = _mm256_loadu_pd(&x[((i0 + 4) + 183)]);
    __mv_vop1628 = _mm256_loadu_pd(&y[((i0 + 0) + 182)]);
    __mv_vop1628 = _mm256_fmadd_pd(__mv_vop258, __mv_vop259, __mv_vop1628);
    _mm256_storeu_pd(&y[((i0 + 0) + 182)], __mv_vop1628);
    __mv_vop1629 = _mm256_loadu_pd(&y[((i0 + 4) + 182)]);
    __mv_vop1629 = _mm256_fmadd_pd(__mv_vop261, __mv_vop262, __mv_vop1629);
    _mm256_storeu_pd(&y[((i0 + 4) + 182)], __mv_vop1629);
    // y[1 * i0 + 182] += A[i0 + 344] * x[1 * i0 + 183];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 182] += A[i0 + 344] * x[1 * i0 + 183];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop264 = _mm256_loadu_pd(&A[((i0 + 0) + 352)]);
    __mv_vop265 = _mm256_loadu_pd(&x[((i0 + 0) + 182)]);
    __mv_vop267 = _mm256_loadu_pd(&A[((i0 + 4) + 352)]);
    __mv_vop268 = _mm256_loadu_pd(&x[((i0 + 4) + 182)]);
    __mv_vop1630 = _mm256_loadu_pd(&y[((i0 + 0) + 183)]);
    __mv_vop1630 = _mm256_fmadd_pd(__mv_vop264, __mv_vop265, __mv_vop1630);
    _mm256_storeu_pd(&y[((i0 + 0) + 183)], __mv_vop1630);
    __mv_vop1631 = _mm256_loadu_pd(&y[((i0 + 4) + 183)]);
    __mv_vop1631 = _mm256_fmadd_pd(__mv_vop267, __mv_vop268, __mv_vop1631);
    _mm256_storeu_pd(&y[((i0 + 4) + 183)], __mv_vop1631);
    // y[1 * i0 + 183] += A[i0 + 352] * x[1 * i0 + 182];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 183] += A[i0 + 352] * x[1 * i0 + 182];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop270 = _mm256_loadu_pd(&A[((i0 + 0) + 360)]);
    __mv_vop271 = _mm256_loadu_pd(&x[((i0 + 0) + 191)]);
    __mv_vop273 = _mm256_loadu_pd(&A[((i0 + 4) + 360)]);
    __mv_vop274 = _mm256_loadu_pd(&x[((i0 + 4) + 191)]);
    __mv_vop1632 = _mm256_loadu_pd(&y[((i0 + 0) + 190)]);
    __mv_vop1632 = _mm256_fmadd_pd(__mv_vop270, __mv_vop271, __mv_vop1632);
    _mm256_storeu_pd(&y[((i0 + 0) + 190)], __mv_vop1632);
    __mv_vop1633 = _mm256_loadu_pd(&y[((i0 + 4) + 190)]);
    __mv_vop1633 = _mm256_fmadd_pd(__mv_vop273, __mv_vop274, __mv_vop1633);
    _mm256_storeu_pd(&y[((i0 + 4) + 190)], __mv_vop1633);
    // y[1 * i0 + 190] += A[i0 + 360] * x[1 * i0 + 191];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 190] += A[i0 + 360] * x[1 * i0 + 191];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop276 = _mm256_loadu_pd(&A[((i0 + 0) + 368)]);
    __mv_vop277 = _mm256_loadu_pd(&x[((i0 + 0) + 190)]);
    __mv_vop279 = _mm256_loadu_pd(&A[((i0 + 4) + 368)]);
    __mv_vop280 = _mm256_loadu_pd(&x[((i0 + 4) + 190)]);
    __mv_vop1634 = _mm256_loadu_pd(&y[((i0 + 0) + 191)]);
    __mv_vop1634 = _mm256_fmadd_pd(__mv_vop276, __mv_vop277, __mv_vop1634);
    _mm256_storeu_pd(&y[((i0 + 0) + 191)], __mv_vop1634);
    __mv_vop1635 = _mm256_loadu_pd(&y[((i0 + 4) + 191)]);
    __mv_vop1635 = _mm256_fmadd_pd(__mv_vop279, __mv_vop280, __mv_vop1635);
    _mm256_storeu_pd(&y[((i0 + 4) + 191)], __mv_vop1635);
    // y[1 * i0 + 191] += A[i0 + 368] * x[1 * i0 + 190];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 191] += A[i0 + 368] * x[1 * i0 + 190];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop282 = _mm256_loadu_pd(&A[((i0 + 0) + 376)]);
    __mv_vop283 = _mm256_loadu_pd(&x[((i0 + 0) + 199)]);
    __mv_vop285 = _mm256_loadu_pd(&A[((i0 + 4) + 376)]);
    __mv_vop286 = _mm256_loadu_pd(&x[((i0 + 4) + 199)]);
    __mv_vop1636 = _mm256_loadu_pd(&y[((i0 + 0) + 198)]);
    __mv_vop1636 = _mm256_fmadd_pd(__mv_vop282, __mv_vop283, __mv_vop1636);
    _mm256_storeu_pd(&y[((i0 + 0) + 198)], __mv_vop1636);
    __mv_vop1637 = _mm256_loadu_pd(&y[((i0 + 4) + 198)]);
    __mv_vop1637 = _mm256_fmadd_pd(__mv_vop285, __mv_vop286, __mv_vop1637);
    _mm256_storeu_pd(&y[((i0 + 4) + 198)], __mv_vop1637);
    // y[1 * i0 + 198] += A[i0 + 376] * x[1 * i0 + 199];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 198] += A[i0 + 376] * x[1 * i0 + 199];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop288 = _mm256_loadu_pd(&A[((i0 + 0) + 384)]);
    __mv_vop289 = _mm256_loadu_pd(&x[((i0 + 0) + 198)]);
    __mv_vop291 = _mm256_loadu_pd(&A[((i0 + 4) + 384)]);
    __mv_vop292 = _mm256_loadu_pd(&x[((i0 + 4) + 198)]);
    __mv_vop1638 = _mm256_loadu_pd(&y[((i0 + 0) + 199)]);
    __mv_vop1638 = _mm256_fmadd_pd(__mv_vop288, __mv_vop289, __mv_vop1638);
    _mm256_storeu_pd(&y[((i0 + 0) + 199)], __mv_vop1638);
    __mv_vop1639 = _mm256_loadu_pd(&y[((i0 + 4) + 199)]);
    __mv_vop1639 = _mm256_fmadd_pd(__mv_vop291, __mv_vop292, __mv_vop1639);
    _mm256_storeu_pd(&y[((i0 + 4) + 199)], __mv_vop1639);
    // y[1 * i0 + 199] += A[i0 + 384] * x[1 * i0 + 198];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 199] += A[i0 + 384] * x[1 * i0 + 198];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop294 = _mm256_loadu_pd(&A[((i0 + 0) + 392)]);
    __mv_vop295 = _mm256_loadu_pd(&x[((i0 + 0) + 207)]);
    __mv_vop297 = _mm256_loadu_pd(&A[((i0 + 4) + 392)]);
    __mv_vop298 = _mm256_loadu_pd(&x[((i0 + 4) + 207)]);
    __mv_vop1640 = _mm256_loadu_pd(&y[((i0 + 0) + 206)]);
    __mv_vop1640 = _mm256_fmadd_pd(__mv_vop294, __mv_vop295, __mv_vop1640);
    _mm256_storeu_pd(&y[((i0 + 0) + 206)], __mv_vop1640);
    __mv_vop1641 = _mm256_loadu_pd(&y[((i0 + 4) + 206)]);
    __mv_vop1641 = _mm256_fmadd_pd(__mv_vop297, __mv_vop298, __mv_vop1641);
    _mm256_storeu_pd(&y[((i0 + 4) + 206)], __mv_vop1641);
    // y[1 * i0 + 206] += A[i0 + 392] * x[1 * i0 + 207];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 206] += A[i0 + 392] * x[1 * i0 + 207];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop300 = _mm256_loadu_pd(&A[((i0 + 0) + 400)]);
    __mv_vop301 = _mm256_loadu_pd(&x[((i0 + 0) + 206)]);
    __mv_vop303 = _mm256_loadu_pd(&A[((i0 + 4) + 400)]);
    __mv_vop304 = _mm256_loadu_pd(&x[((i0 + 4) + 206)]);
    __mv_vop1642 = _mm256_loadu_pd(&y[((i0 + 0) + 207)]);
    __mv_vop1642 = _mm256_fmadd_pd(__mv_vop300, __mv_vop301, __mv_vop1642);
    _mm256_storeu_pd(&y[((i0 + 0) + 207)], __mv_vop1642);
    __mv_vop1643 = _mm256_loadu_pd(&y[((i0 + 4) + 207)]);
    __mv_vop1643 = _mm256_fmadd_pd(__mv_vop303, __mv_vop304, __mv_vop1643);
    _mm256_storeu_pd(&y[((i0 + 4) + 207)], __mv_vop1643);
    // y[1 * i0 + 207] += A[i0 + 400] * x[1 * i0 + 206];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 207] += A[i0 + 400] * x[1 * i0 + 206];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop306 = _mm256_loadu_pd(&A[((i0 + 0) + 408)]);
    __mv_vop307 = _mm256_loadu_pd(&x[((i0 + 0) + 215)]);
    __mv_vop309 = _mm256_loadu_pd(&A[((i0 + 4) + 408)]);
    __mv_vop310 = _mm256_loadu_pd(&x[((i0 + 4) + 215)]);
    __mv_vop1644 = _mm256_loadu_pd(&y[((i0 + 0) + 214)]);
    __mv_vop1644 = _mm256_fmadd_pd(__mv_vop306, __mv_vop307, __mv_vop1644);
    _mm256_storeu_pd(&y[((i0 + 0) + 214)], __mv_vop1644);
    __mv_vop1645 = _mm256_loadu_pd(&y[((i0 + 4) + 214)]);
    __mv_vop1645 = _mm256_fmadd_pd(__mv_vop309, __mv_vop310, __mv_vop1645);
    _mm256_storeu_pd(&y[((i0 + 4) + 214)], __mv_vop1645);
    // y[1 * i0 + 214] += A[i0 + 408] * x[1 * i0 + 215];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 214] += A[i0 + 408] * x[1 * i0 + 215];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop312 = _mm256_loadu_pd(&A[((i0 + 0) + 416)]);
    __mv_vop313 = _mm256_loadu_pd(&x[((i0 + 0) + 214)]);
    __mv_vop315 = _mm256_loadu_pd(&A[((i0 + 4) + 416)]);
    __mv_vop316 = _mm256_loadu_pd(&x[((i0 + 4) + 214)]);
    __mv_vop1646 = _mm256_loadu_pd(&y[((i0 + 0) + 215)]);
    __mv_vop1646 = _mm256_fmadd_pd(__mv_vop312, __mv_vop313, __mv_vop1646);
    _mm256_storeu_pd(&y[((i0 + 0) + 215)], __mv_vop1646);
    __mv_vop1647 = _mm256_loadu_pd(&y[((i0 + 4) + 215)]);
    __mv_vop1647 = _mm256_fmadd_pd(__mv_vop315, __mv_vop316, __mv_vop1647);
    _mm256_storeu_pd(&y[((i0 + 4) + 215)], __mv_vop1647);
    // y[1 * i0 + 215] += A[i0 + 416] * x[1 * i0 + 214];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 215] += A[i0 + 416] * x[1 * i0 + 214];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop318 = _mm256_loadu_pd(&A[((i0 + 0) + 424)]);
    __mv_vop319 = _mm256_loadu_pd(&x[((i0 + 0) + 223)]);
    __mv_vop321 = _mm256_loadu_pd(&A[((i0 + 4) + 424)]);
    __mv_vop322 = _mm256_loadu_pd(&x[((i0 + 4) + 223)]);
    __mv_vop1648 = _mm256_loadu_pd(&y[((i0 + 0) + 222)]);
    __mv_vop1648 = _mm256_fmadd_pd(__mv_vop318, __mv_vop319, __mv_vop1648);
    _mm256_storeu_pd(&y[((i0 + 0) + 222)], __mv_vop1648);
    __mv_vop1649 = _mm256_loadu_pd(&y[((i0 + 4) + 222)]);
    __mv_vop1649 = _mm256_fmadd_pd(__mv_vop321, __mv_vop322, __mv_vop1649);
    _mm256_storeu_pd(&y[((i0 + 4) + 222)], __mv_vop1649);
    // y[1 * i0 + 222] += A[i0 + 424] * x[1 * i0 + 223];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 222] += A[i0 + 424] * x[1 * i0 + 223];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop324 = _mm256_loadu_pd(&A[((i0 + 0) + 432)]);
    __mv_vop325 = _mm256_loadu_pd(&x[((i0 + 0) + 222)]);
    __mv_vop327 = _mm256_loadu_pd(&A[((i0 + 4) + 432)]);
    __mv_vop328 = _mm256_loadu_pd(&x[((i0 + 4) + 222)]);
    __mv_vop1650 = _mm256_loadu_pd(&y[((i0 + 0) + 223)]);
    __mv_vop1650 = _mm256_fmadd_pd(__mv_vop324, __mv_vop325, __mv_vop1650);
    _mm256_storeu_pd(&y[((i0 + 0) + 223)], __mv_vop1650);
    __mv_vop1651 = _mm256_loadu_pd(&y[((i0 + 4) + 223)]);
    __mv_vop1651 = _mm256_fmadd_pd(__mv_vop327, __mv_vop328, __mv_vop1651);
    _mm256_storeu_pd(&y[((i0 + 4) + 223)], __mv_vop1651);
    // y[1 * i0 + 223] += A[i0 + 432] * x[1 * i0 + 222];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 223] += A[i0 + 432] * x[1 * i0 + 222];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop330 = _mm256_loadu_pd(&A[((i0 + 0) + 440)]);
    __mv_vop331 = _mm256_loadu_pd(&x[((i0 + 0) + 231)]);
    __mv_vop333 = _mm256_loadu_pd(&A[((i0 + 4) + 440)]);
    __mv_vop334 = _mm256_loadu_pd(&x[((i0 + 4) + 231)]);
    __mv_vop1652 = _mm256_loadu_pd(&y[((i0 + 0) + 230)]);
    __mv_vop1652 = _mm256_fmadd_pd(__mv_vop330, __mv_vop331, __mv_vop1652);
    _mm256_storeu_pd(&y[((i0 + 0) + 230)], __mv_vop1652);
    __mv_vop1653 = _mm256_loadu_pd(&y[((i0 + 4) + 230)]);
    __mv_vop1653 = _mm256_fmadd_pd(__mv_vop333, __mv_vop334, __mv_vop1653);
    _mm256_storeu_pd(&y[((i0 + 4) + 230)], __mv_vop1653);
    // y[1 * i0 + 230] += A[i0 + 440] * x[1 * i0 + 231];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 230] += A[i0 + 440] * x[1 * i0 + 231];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop336 = _mm256_loadu_pd(&A[((i0 + 0) + 448)]);
    __mv_vop337 = _mm256_loadu_pd(&x[((i0 + 0) + 230)]);
    __mv_vop339 = _mm256_loadu_pd(&A[((i0 + 4) + 448)]);
    __mv_vop340 = _mm256_loadu_pd(&x[((i0 + 4) + 230)]);
    __mv_vop1654 = _mm256_loadu_pd(&y[((i0 + 0) + 231)]);
    __mv_vop1654 = _mm256_fmadd_pd(__mv_vop336, __mv_vop337, __mv_vop1654);
    _mm256_storeu_pd(&y[((i0 + 0) + 231)], __mv_vop1654);
    __mv_vop1655 = _mm256_loadu_pd(&y[((i0 + 4) + 231)]);
    __mv_vop1655 = _mm256_fmadd_pd(__mv_vop339, __mv_vop340, __mv_vop1655);
    _mm256_storeu_pd(&y[((i0 + 4) + 231)], __mv_vop1655);
    // y[1 * i0 + 231] += A[i0 + 448] * x[1 * i0 + 230];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 231] += A[i0 + 448] * x[1 * i0 + 230];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop342 = _mm256_loadu_pd(&A[((i0 + 0) + 456)]);
    __mv_vop343 = _mm256_loadu_pd(&x[((i0 + 0) + 239)]);
    __mv_vop345 = _mm256_loadu_pd(&A[((i0 + 4) + 456)]);
    __mv_vop346 = _mm256_loadu_pd(&x[((i0 + 4) + 239)]);
    __mv_vop1656 = _mm256_loadu_pd(&y[((i0 + 0) + 238)]);
    __mv_vop1656 = _mm256_fmadd_pd(__mv_vop342, __mv_vop343, __mv_vop1656);
    _mm256_storeu_pd(&y[((i0 + 0) + 238)], __mv_vop1656);
    __mv_vop1657 = _mm256_loadu_pd(&y[((i0 + 4) + 238)]);
    __mv_vop1657 = _mm256_fmadd_pd(__mv_vop345, __mv_vop346, __mv_vop1657);
    _mm256_storeu_pd(&y[((i0 + 4) + 238)], __mv_vop1657);
    // y[1 * i0 + 238] += A[i0 + 456] * x[1 * i0 + 239];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 238] += A[i0 + 456] * x[1 * i0 + 239];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop348 = _mm256_loadu_pd(&A[((i0 + 0) + 464)]);
    __mv_vop349 = _mm256_loadu_pd(&x[((i0 + 0) + 238)]);
    __mv_vop351 = _mm256_loadu_pd(&A[((i0 + 4) + 464)]);
    __mv_vop352 = _mm256_loadu_pd(&x[((i0 + 4) + 238)]);
    __mv_vop1658 = _mm256_loadu_pd(&y[((i0 + 0) + 239)]);
    __mv_vop1658 = _mm256_fmadd_pd(__mv_vop348, __mv_vop349, __mv_vop1658);
    _mm256_storeu_pd(&y[((i0 + 0) + 239)], __mv_vop1658);
    __mv_vop1659 = _mm256_loadu_pd(&y[((i0 + 4) + 239)]);
    __mv_vop1659 = _mm256_fmadd_pd(__mv_vop351, __mv_vop352, __mv_vop1659);
    _mm256_storeu_pd(&y[((i0 + 4) + 239)], __mv_vop1659);
    // y[1 * i0 + 239] += A[i0 + 464] * x[1 * i0 + 238];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 239] += A[i0 + 464] * x[1 * i0 + 238];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop354 = _mm256_loadu_pd(&A[((i0 + 0) + 472)]);
    __mv_vop355 = _mm256_loadu_pd(&x[((i0 + 0) + 247)]);
    __mv_vop357 = _mm256_loadu_pd(&A[((i0 + 4) + 472)]);
    __mv_vop358 = _mm256_loadu_pd(&x[((i0 + 4) + 247)]);
    __mv_vop1660 = _mm256_loadu_pd(&y[((i0 + 0) + 246)]);
    __mv_vop1660 = _mm256_fmadd_pd(__mv_vop354, __mv_vop355, __mv_vop1660);
    _mm256_storeu_pd(&y[((i0 + 0) + 246)], __mv_vop1660);
    __mv_vop1661 = _mm256_loadu_pd(&y[((i0 + 4) + 246)]);
    __mv_vop1661 = _mm256_fmadd_pd(__mv_vop357, __mv_vop358, __mv_vop1661);
    _mm256_storeu_pd(&y[((i0 + 4) + 246)], __mv_vop1661);
    // y[1 * i0 + 246] += A[i0 + 472] * x[1 * i0 + 247];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 246] += A[i0 + 472] * x[1 * i0 + 247];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop360 = _mm256_loadu_pd(&A[((i0 + 0) + 480)]);
    __mv_vop361 = _mm256_loadu_pd(&x[((i0 + 0) + 246)]);
    __mv_vop363 = _mm256_loadu_pd(&A[((i0 + 4) + 480)]);
    __mv_vop364 = _mm256_loadu_pd(&x[((i0 + 4) + 246)]);
    __mv_vop1662 = _mm256_loadu_pd(&y[((i0 + 0) + 247)]);
    __mv_vop1662 = _mm256_fmadd_pd(__mv_vop360, __mv_vop361, __mv_vop1662);
    _mm256_storeu_pd(&y[((i0 + 0) + 247)], __mv_vop1662);
    __mv_vop1663 = _mm256_loadu_pd(&y[((i0 + 4) + 247)]);
    __mv_vop1663 = _mm256_fmadd_pd(__mv_vop363, __mv_vop364, __mv_vop1663);
    _mm256_storeu_pd(&y[((i0 + 4) + 247)], __mv_vop1663);
    // y[1 * i0 + 247] += A[i0 + 480] * x[1 * i0 + 246];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 247] += A[i0 + 480] * x[1 * i0 + 246];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop366 = _mm256_loadu_pd(&A[((i0 + 0) + 488)]);
    __mv_vop367 = _mm256_loadu_pd(&x[((i0 + 0) + 255)]);
    __mv_vop369 = _mm256_loadu_pd(&A[((i0 + 4) + 488)]);
    __mv_vop370 = _mm256_loadu_pd(&x[((i0 + 4) + 255)]);
    __mv_vop1664 = _mm256_loadu_pd(&y[((i0 + 0) + 254)]);
    __mv_vop1664 = _mm256_fmadd_pd(__mv_vop366, __mv_vop367, __mv_vop1664);
    _mm256_storeu_pd(&y[((i0 + 0) + 254)], __mv_vop1664);
    __mv_vop1665 = _mm256_loadu_pd(&y[((i0 + 4) + 254)]);
    __mv_vop1665 = _mm256_fmadd_pd(__mv_vop369, __mv_vop370, __mv_vop1665);
    _mm256_storeu_pd(&y[((i0 + 4) + 254)], __mv_vop1665);
    // y[1 * i0 + 254] += A[i0 + 488] * x[1 * i0 + 255];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 254] += A[i0 + 488] * x[1 * i0 + 255];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop372 = _mm256_loadu_pd(&A[((i0 + 0) + 496)]);
    __mv_vop373 = _mm256_loadu_pd(&x[((i0 + 0) + 254)]);
    __mv_vop375 = _mm256_loadu_pd(&A[((i0 + 4) + 496)]);
    __mv_vop376 = _mm256_loadu_pd(&x[((i0 + 4) + 254)]);
    __mv_vop1666 = _mm256_loadu_pd(&y[((i0 + 0) + 255)]);
    __mv_vop1666 = _mm256_fmadd_pd(__mv_vop372, __mv_vop373, __mv_vop1666);
    _mm256_storeu_pd(&y[((i0 + 0) + 255)], __mv_vop1666);
    __mv_vop1667 = _mm256_loadu_pd(&y[((i0 + 4) + 255)]);
    __mv_vop1667 = _mm256_fmadd_pd(__mv_vop375, __mv_vop376, __mv_vop1667);
    _mm256_storeu_pd(&y[((i0 + 4) + 255)], __mv_vop1667);
    // y[1 * i0 + 255] += A[i0 + 496] * x[1 * i0 + 254];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 255] += A[i0 + 496] * x[1 * i0 + 254];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop378 = _mm256_loadu_pd(&A[((i0 + 0) + 504)]);
    __mv_vop379 = _mm256_loadu_pd(&x[((i0 + 0) + 263)]);
    __mv_vop381 = _mm256_loadu_pd(&A[((i0 + 4) + 504)]);
    __mv_vop382 = _mm256_loadu_pd(&x[((i0 + 4) + 263)]);
    __mv_vop1668 = _mm256_loadu_pd(&y[((i0 + 0) + 262)]);
    __mv_vop1668 = _mm256_fmadd_pd(__mv_vop378, __mv_vop379, __mv_vop1668);
    _mm256_storeu_pd(&y[((i0 + 0) + 262)], __mv_vop1668);
    __mv_vop1669 = _mm256_loadu_pd(&y[((i0 + 4) + 262)]);
    __mv_vop1669 = _mm256_fmadd_pd(__mv_vop381, __mv_vop382, __mv_vop1669);
    _mm256_storeu_pd(&y[((i0 + 4) + 262)], __mv_vop1669);
    // y[1 * i0 + 262] += A[i0 + 504] * x[1 * i0 + 263];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 262] += A[i0 + 504] * x[1 * i0 + 263];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop384 = _mm256_loadu_pd(&A[((i0 + 0) + 512)]);
    __mv_vop385 = _mm256_loadu_pd(&x[((i0 + 0) + 262)]);
    __mv_vop387 = _mm256_loadu_pd(&A[((i0 + 4) + 512)]);
    __mv_vop388 = _mm256_loadu_pd(&x[((i0 + 4) + 262)]);
    __mv_vop1670 = _mm256_loadu_pd(&y[((i0 + 0) + 263)]);
    __mv_vop1670 = _mm256_fmadd_pd(__mv_vop384, __mv_vop385, __mv_vop1670);
    _mm256_storeu_pd(&y[((i0 + 0) + 263)], __mv_vop1670);
    __mv_vop1671 = _mm256_loadu_pd(&y[((i0 + 4) + 263)]);
    __mv_vop1671 = _mm256_fmadd_pd(__mv_vop387, __mv_vop388, __mv_vop1671);
    _mm256_storeu_pd(&y[((i0 + 4) + 263)], __mv_vop1671);
    // y[1 * i0 + 263] += A[i0 + 512] * x[1 * i0 + 262];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 263] += A[i0 + 512] * x[1 * i0 + 262];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop390 = _mm256_loadu_pd(&A[((i0 + 0) + 520)]);
    __mv_vop391 = _mm256_loadu_pd(&x[((i0 + 0) + 271)]);
    __mv_vop393 = _mm256_loadu_pd(&A[((i0 + 4) + 520)]);
    __mv_vop394 = _mm256_loadu_pd(&x[((i0 + 4) + 271)]);
    __mv_vop1672 = _mm256_loadu_pd(&y[((i0 + 0) + 270)]);
    __mv_vop1672 = _mm256_fmadd_pd(__mv_vop390, __mv_vop391, __mv_vop1672);
    _mm256_storeu_pd(&y[((i0 + 0) + 270)], __mv_vop1672);
    __mv_vop1673 = _mm256_loadu_pd(&y[((i0 + 4) + 270)]);
    __mv_vop1673 = _mm256_fmadd_pd(__mv_vop393, __mv_vop394, __mv_vop1673);
    _mm256_storeu_pd(&y[((i0 + 4) + 270)], __mv_vop1673);
    // y[1 * i0 + 270] += A[i0 + 520] * x[1 * i0 + 271];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 270] += A[i0 + 520] * x[1 * i0 + 271];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop396 = _mm256_loadu_pd(&A[((i0 + 0) + 528)]);
    __mv_vop397 = _mm256_loadu_pd(&x[((i0 + 0) + 270)]);
    __mv_vop399 = _mm256_loadu_pd(&A[((i0 + 4) + 528)]);
    __mv_vop400 = _mm256_loadu_pd(&x[((i0 + 4) + 270)]);
    __mv_vop1674 = _mm256_loadu_pd(&y[((i0 + 0) + 271)]);
    __mv_vop1674 = _mm256_fmadd_pd(__mv_vop396, __mv_vop397, __mv_vop1674);
    _mm256_storeu_pd(&y[((i0 + 0) + 271)], __mv_vop1674);
    __mv_vop1675 = _mm256_loadu_pd(&y[((i0 + 4) + 271)]);
    __mv_vop1675 = _mm256_fmadd_pd(__mv_vop399, __mv_vop400, __mv_vop1675);
    _mm256_storeu_pd(&y[((i0 + 4) + 271)], __mv_vop1675);
    // y[1 * i0 + 271] += A[i0 + 528] * x[1 * i0 + 270];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 271] += A[i0 + 528] * x[1 * i0 + 270];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop402 = _mm256_loadu_pd(&A[((i0 + 0) + 536)]);
    __mv_vop403 = _mm256_loadu_pd(&x[((i0 + 0) + 279)]);
    __mv_vop405 = _mm256_loadu_pd(&A[((i0 + 4) + 536)]);
    __mv_vop406 = _mm256_loadu_pd(&x[((i0 + 4) + 279)]);
    __mv_vop1676 = _mm256_loadu_pd(&y[((i0 + 0) + 278)]);
    __mv_vop1676 = _mm256_fmadd_pd(__mv_vop402, __mv_vop403, __mv_vop1676);
    _mm256_storeu_pd(&y[((i0 + 0) + 278)], __mv_vop1676);
    __mv_vop1677 = _mm256_loadu_pd(&y[((i0 + 4) + 278)]);
    __mv_vop1677 = _mm256_fmadd_pd(__mv_vop405, __mv_vop406, __mv_vop1677);
    _mm256_storeu_pd(&y[((i0 + 4) + 278)], __mv_vop1677);
    // y[1 * i0 + 278] += A[i0 + 536] * x[1 * i0 + 279];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 278] += A[i0 + 536] * x[1 * i0 + 279];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop408 = _mm256_loadu_pd(&A[((i0 + 0) + 544)]);
    __mv_vop409 = _mm256_loadu_pd(&x[((i0 + 0) + 278)]);
    __mv_vop411 = _mm256_loadu_pd(&A[((i0 + 4) + 544)]);
    __mv_vop412 = _mm256_loadu_pd(&x[((i0 + 4) + 278)]);
    __mv_vop1678 = _mm256_loadu_pd(&y[((i0 + 0) + 279)]);
    __mv_vop1678 = _mm256_fmadd_pd(__mv_vop408, __mv_vop409, __mv_vop1678);
    _mm256_storeu_pd(&y[((i0 + 0) + 279)], __mv_vop1678);
    __mv_vop1679 = _mm256_loadu_pd(&y[((i0 + 4) + 279)]);
    __mv_vop1679 = _mm256_fmadd_pd(__mv_vop411, __mv_vop412, __mv_vop1679);
    _mm256_storeu_pd(&y[((i0 + 4) + 279)], __mv_vop1679);
    // y[1 * i0 + 279] += A[i0 + 544] * x[1 * i0 + 278];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 279] += A[i0 + 544] * x[1 * i0 + 278];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop414 = _mm256_loadu_pd(&A[((i0 + 0) + 552)]);
    __mv_vop415 = _mm256_loadu_pd(&x[((i0 + 0) + 287)]);
    __mv_vop417 = _mm256_loadu_pd(&A[((i0 + 4) + 552)]);
    __mv_vop418 = _mm256_loadu_pd(&x[((i0 + 4) + 287)]);
    __mv_vop1680 = _mm256_loadu_pd(&y[((i0 + 0) + 286)]);
    __mv_vop1680 = _mm256_fmadd_pd(__mv_vop414, __mv_vop415, __mv_vop1680);
    _mm256_storeu_pd(&y[((i0 + 0) + 286)], __mv_vop1680);
    __mv_vop1681 = _mm256_loadu_pd(&y[((i0 + 4) + 286)]);
    __mv_vop1681 = _mm256_fmadd_pd(__mv_vop417, __mv_vop418, __mv_vop1681);
    _mm256_storeu_pd(&y[((i0 + 4) + 286)], __mv_vop1681);
    // y[1 * i0 + 286] += A[i0 + 552] * x[1 * i0 + 287];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 286] += A[i0 + 552] * x[1 * i0 + 287];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop420 = _mm256_loadu_pd(&A[((i0 + 0) + 560)]);
    __mv_vop421 = _mm256_loadu_pd(&x[((i0 + 0) + 286)]);
    __mv_vop423 = _mm256_loadu_pd(&A[((i0 + 4) + 560)]);
    __mv_vop424 = _mm256_loadu_pd(&x[((i0 + 4) + 286)]);
    __mv_vop1682 = _mm256_loadu_pd(&y[((i0 + 0) + 287)]);
    __mv_vop1682 = _mm256_fmadd_pd(__mv_vop420, __mv_vop421, __mv_vop1682);
    _mm256_storeu_pd(&y[((i0 + 0) + 287)], __mv_vop1682);
    __mv_vop1683 = _mm256_loadu_pd(&y[((i0 + 4) + 287)]);
    __mv_vop1683 = _mm256_fmadd_pd(__mv_vop423, __mv_vop424, __mv_vop1683);
    _mm256_storeu_pd(&y[((i0 + 4) + 287)], __mv_vop1683);
    // y[1 * i0 + 287] += A[i0 + 560] * x[1 * i0 + 286];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 287] += A[i0 + 560] * x[1 * i0 + 286];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop426 = _mm256_loadu_pd(&A[((i0 + 0) + 568)]);
    __mv_vop427 = _mm256_loadu_pd(&x[((i0 + 0) + 295)]);
    __mv_vop429 = _mm256_loadu_pd(&A[((i0 + 4) + 568)]);
    __mv_vop430 = _mm256_loadu_pd(&x[((i0 + 4) + 295)]);
    __mv_vop1684 = _mm256_loadu_pd(&y[((i0 + 0) + 294)]);
    __mv_vop1684 = _mm256_fmadd_pd(__mv_vop426, __mv_vop427, __mv_vop1684);
    _mm256_storeu_pd(&y[((i0 + 0) + 294)], __mv_vop1684);
    __mv_vop1685 = _mm256_loadu_pd(&y[((i0 + 4) + 294)]);
    __mv_vop1685 = _mm256_fmadd_pd(__mv_vop429, __mv_vop430, __mv_vop1685);
    _mm256_storeu_pd(&y[((i0 + 4) + 294)], __mv_vop1685);
    // y[1 * i0 + 294] += A[i0 + 568] * x[1 * i0 + 295];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 294] += A[i0 + 568] * x[1 * i0 + 295];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop432 = _mm256_loadu_pd(&A[((i0 + 0) + 576)]);
    __mv_vop433 = _mm256_loadu_pd(&x[((i0 + 0) + 294)]);
    __mv_vop435 = _mm256_loadu_pd(&A[((i0 + 4) + 576)]);
    __mv_vop436 = _mm256_loadu_pd(&x[((i0 + 4) + 294)]);
    __mv_vop1686 = _mm256_loadu_pd(&y[((i0 + 0) + 295)]);
    __mv_vop1686 = _mm256_fmadd_pd(__mv_vop432, __mv_vop433, __mv_vop1686);
    _mm256_storeu_pd(&y[((i0 + 0) + 295)], __mv_vop1686);
    __mv_vop1687 = _mm256_loadu_pd(&y[((i0 + 4) + 295)]);
    __mv_vop1687 = _mm256_fmadd_pd(__mv_vop435, __mv_vop436, __mv_vop1687);
    _mm256_storeu_pd(&y[((i0 + 4) + 295)], __mv_vop1687);
    // y[1 * i0 + 295] += A[i0 + 576] * x[1 * i0 + 294];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 295] += A[i0 + 576] * x[1 * i0 + 294];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop438 = _mm256_loadu_pd(&A[((i0 + 0) + 584)]);
    __mv_vop439 = _mm256_loadu_pd(&x[((i0 + 0) + 303)]);
    __mv_vop441 = _mm256_loadu_pd(&A[((i0 + 4) + 584)]);
    __mv_vop442 = _mm256_loadu_pd(&x[((i0 + 4) + 303)]);
    __mv_vop1688 = _mm256_loadu_pd(&y[((i0 + 0) + 302)]);
    __mv_vop1688 = _mm256_fmadd_pd(__mv_vop438, __mv_vop439, __mv_vop1688);
    _mm256_storeu_pd(&y[((i0 + 0) + 302)], __mv_vop1688);
    __mv_vop1689 = _mm256_loadu_pd(&y[((i0 + 4) + 302)]);
    __mv_vop1689 = _mm256_fmadd_pd(__mv_vop441, __mv_vop442, __mv_vop1689);
    _mm256_storeu_pd(&y[((i0 + 4) + 302)], __mv_vop1689);
    // y[1 * i0 + 302] += A[i0 + 584] * x[1 * i0 + 303];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 302] += A[i0 + 584] * x[1 * i0 + 303];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop444 = _mm256_loadu_pd(&A[((i0 + 0) + 592)]);
    __mv_vop445 = _mm256_loadu_pd(&x[((i0 + 0) + 302)]);
    __mv_vop447 = _mm256_loadu_pd(&A[((i0 + 4) + 592)]);
    __mv_vop448 = _mm256_loadu_pd(&x[((i0 + 4) + 302)]);
    __mv_vop1690 = _mm256_loadu_pd(&y[((i0 + 0) + 303)]);
    __mv_vop1690 = _mm256_fmadd_pd(__mv_vop444, __mv_vop445, __mv_vop1690);
    _mm256_storeu_pd(&y[((i0 + 0) + 303)], __mv_vop1690);
    __mv_vop1691 = _mm256_loadu_pd(&y[((i0 + 4) + 303)]);
    __mv_vop1691 = _mm256_fmadd_pd(__mv_vop447, __mv_vop448, __mv_vop1691);
    _mm256_storeu_pd(&y[((i0 + 4) + 303)], __mv_vop1691);
    // y[1 * i0 + 303] += A[i0 + 592] * x[1 * i0 + 302];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 303] += A[i0 + 592] * x[1 * i0 + 302];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop450 = _mm256_loadu_pd(&A[((i0 + 0) + 600)]);
    __mv_vop451 = _mm256_loadu_pd(&x[((i0 + 0) + 311)]);
    __mv_vop453 = _mm256_loadu_pd(&A[((i0 + 4) + 600)]);
    __mv_vop454 = _mm256_loadu_pd(&x[((i0 + 4) + 311)]);
    __mv_vop1692 = _mm256_loadu_pd(&y[((i0 + 0) + 310)]);
    __mv_vop1692 = _mm256_fmadd_pd(__mv_vop450, __mv_vop451, __mv_vop1692);
    _mm256_storeu_pd(&y[((i0 + 0) + 310)], __mv_vop1692);
    __mv_vop1693 = _mm256_loadu_pd(&y[((i0 + 4) + 310)]);
    __mv_vop1693 = _mm256_fmadd_pd(__mv_vop453, __mv_vop454, __mv_vop1693);
    _mm256_storeu_pd(&y[((i0 + 4) + 310)], __mv_vop1693);
    // y[1 * i0 + 310] += A[i0 + 600] * x[1 * i0 + 311];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 310] += A[i0 + 600] * x[1 * i0 + 311];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop456 = _mm256_loadu_pd(&A[((i0 + 0) + 608)]);
    __mv_vop457 = _mm256_loadu_pd(&x[((i0 + 0) + 310)]);
    __mv_vop459 = _mm256_loadu_pd(&A[((i0 + 4) + 608)]);
    __mv_vop460 = _mm256_loadu_pd(&x[((i0 + 4) + 310)]);
    __mv_vop1694 = _mm256_loadu_pd(&y[((i0 + 0) + 311)]);
    __mv_vop1694 = _mm256_fmadd_pd(__mv_vop456, __mv_vop457, __mv_vop1694);
    _mm256_storeu_pd(&y[((i0 + 0) + 311)], __mv_vop1694);
    __mv_vop1695 = _mm256_loadu_pd(&y[((i0 + 4) + 311)]);
    __mv_vop1695 = _mm256_fmadd_pd(__mv_vop459, __mv_vop460, __mv_vop1695);
    _mm256_storeu_pd(&y[((i0 + 4) + 311)], __mv_vop1695);
    // y[1 * i0 + 311] += A[i0 + 608] * x[1 * i0 + 310];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 311] += A[i0 + 608] * x[1 * i0 + 310];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop462 = _mm256_loadu_pd(&A[((i0 + 0) + 616)]);
    __mv_vop463 = _mm256_loadu_pd(&x[((i0 + 0) + 319)]);
    __mv_vop465 = _mm256_loadu_pd(&A[((i0 + 4) + 616)]);
    __mv_vop466 = _mm256_loadu_pd(&x[((i0 + 4) + 319)]);
    __mv_vop1696 = _mm256_loadu_pd(&y[((i0 + 0) + 318)]);
    __mv_vop1696 = _mm256_fmadd_pd(__mv_vop462, __mv_vop463, __mv_vop1696);
    _mm256_storeu_pd(&y[((i0 + 0) + 318)], __mv_vop1696);
    __mv_vop1697 = _mm256_loadu_pd(&y[((i0 + 4) + 318)]);
    __mv_vop1697 = _mm256_fmadd_pd(__mv_vop465, __mv_vop466, __mv_vop1697);
    _mm256_storeu_pd(&y[((i0 + 4) + 318)], __mv_vop1697);
    // y[1 * i0 + 318] += A[i0 + 616] * x[1 * i0 + 319];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 318] += A[i0 + 616] * x[1 * i0 + 319];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop468 = _mm256_loadu_pd(&A[((i0 + 0) + 624)]);
    __mv_vop469 = _mm256_loadu_pd(&x[((i0 + 0) + 318)]);
    __mv_vop471 = _mm256_loadu_pd(&A[((i0 + 4) + 624)]);
    __mv_vop472 = _mm256_loadu_pd(&x[((i0 + 4) + 318)]);
    __mv_vop1698 = _mm256_loadu_pd(&y[((i0 + 0) + 319)]);
    __mv_vop1698 = _mm256_fmadd_pd(__mv_vop468, __mv_vop469, __mv_vop1698);
    _mm256_storeu_pd(&y[((i0 + 0) + 319)], __mv_vop1698);
    __mv_vop1699 = _mm256_loadu_pd(&y[((i0 + 4) + 319)]);
    __mv_vop1699 = _mm256_fmadd_pd(__mv_vop471, __mv_vop472, __mv_vop1699);
    _mm256_storeu_pd(&y[((i0 + 4) + 319)], __mv_vop1699);
    // y[1 * i0 + 319] += A[i0 + 624] * x[1 * i0 + 318];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 319] += A[i0 + 624] * x[1 * i0 + 318];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop474 = _mm256_loadu_pd(&A[((i0 + 0) + 632)]);
    __mv_vop475 = _mm256_loadu_pd(&x[((i0 + 0) + 327)]);
    __mv_vop477 = _mm256_loadu_pd(&A[((i0 + 4) + 632)]);
    __mv_vop478 = _mm256_loadu_pd(&x[((i0 + 4) + 327)]);
    __mv_vop1700 = _mm256_loadu_pd(&y[((i0 + 0) + 326)]);
    __mv_vop1700 = _mm256_fmadd_pd(__mv_vop474, __mv_vop475, __mv_vop1700);
    _mm256_storeu_pd(&y[((i0 + 0) + 326)], __mv_vop1700);
    __mv_vop1701 = _mm256_loadu_pd(&y[((i0 + 4) + 326)]);
    __mv_vop1701 = _mm256_fmadd_pd(__mv_vop477, __mv_vop478, __mv_vop1701);
    _mm256_storeu_pd(&y[((i0 + 4) + 326)], __mv_vop1701);
    // y[1 * i0 + 326] += A[i0 + 632] * x[1 * i0 + 327];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 326] += A[i0 + 632] * x[1 * i0 + 327];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop480 = _mm256_loadu_pd(&A[((i0 + 0) + 640)]);
    __mv_vop481 = _mm256_loadu_pd(&x[((i0 + 0) + 326)]);
    __mv_vop483 = _mm256_loadu_pd(&A[((i0 + 4) + 640)]);
    __mv_vop484 = _mm256_loadu_pd(&x[((i0 + 4) + 326)]);
    __mv_vop1702 = _mm256_loadu_pd(&y[((i0 + 0) + 327)]);
    __mv_vop1702 = _mm256_fmadd_pd(__mv_vop480, __mv_vop481, __mv_vop1702);
    _mm256_storeu_pd(&y[((i0 + 0) + 327)], __mv_vop1702);
    __mv_vop1703 = _mm256_loadu_pd(&y[((i0 + 4) + 327)]);
    __mv_vop1703 = _mm256_fmadd_pd(__mv_vop483, __mv_vop484, __mv_vop1703);
    _mm256_storeu_pd(&y[((i0 + 4) + 327)], __mv_vop1703);
    // y[1 * i0 + 327] += A[i0 + 640] * x[1 * i0 + 326];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 327] += A[i0 + 640] * x[1 * i0 + 326];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop486 = _mm256_loadu_pd(&A[((i0 + 0) + 648)]);
    __mv_vop487 = _mm256_loadu_pd(&x[((i0 + 0) + 336)]);
    __mv_vop489 = _mm256_loadu_pd(&A[((i0 + 4) + 648)]);
    __mv_vop490 = _mm256_loadu_pd(&x[((i0 + 4) + 336)]);
    __mv_vop1704 = _mm256_loadu_pd(&y[((i0 + 0) + 335)]);
    __mv_vop1704 = _mm256_fmadd_pd(__mv_vop486, __mv_vop487, __mv_vop1704);
    _mm256_storeu_pd(&y[((i0 + 0) + 335)], __mv_vop1704);
    __mv_vop1705 = _mm256_loadu_pd(&y[((i0 + 4) + 335)]);
    __mv_vop1705 = _mm256_fmadd_pd(__mv_vop489, __mv_vop490, __mv_vop1705);
    _mm256_storeu_pd(&y[((i0 + 4) + 335)], __mv_vop1705);
    // y[1 * i0 + 335] += A[i0 + 648] * x[1 * i0 + 336];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 335] += A[i0 + 648] * x[1 * i0 + 336];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop492 = _mm256_loadu_pd(&A[((i0 + 0) + 656)]);
    __mv_vop493 = _mm256_loadu_pd(&x[((i0 + 0) + 335)]);
    __mv_vop495 = _mm256_loadu_pd(&A[((i0 + 4) + 656)]);
    __mv_vop496 = _mm256_loadu_pd(&x[((i0 + 4) + 335)]);
    __mv_vop1706 = _mm256_loadu_pd(&y[((i0 + 0) + 336)]);
    __mv_vop1706 = _mm256_fmadd_pd(__mv_vop492, __mv_vop493, __mv_vop1706);
    _mm256_storeu_pd(&y[((i0 + 0) + 336)], __mv_vop1706);
    __mv_vop1707 = _mm256_loadu_pd(&y[((i0 + 4) + 336)]);
    __mv_vop1707 = _mm256_fmadd_pd(__mv_vop495, __mv_vop496, __mv_vop1707);
    _mm256_storeu_pd(&y[((i0 + 4) + 336)], __mv_vop1707);
    // y[1 * i0 + 336] += A[i0 + 656] * x[1 * i0 + 335];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 336] += A[i0 + 656] * x[1 * i0 + 335];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop498 = _mm256_loadu_pd(&A[((i0 + 0) + 664)]);
    __mv_vop499 = _mm256_loadu_pd(&x[((i0 + 0) + 344)]);
    __mv_vop501 = _mm256_loadu_pd(&A[((i0 + 4) + 664)]);
    __mv_vop502 = _mm256_loadu_pd(&x[((i0 + 4) + 344)]);
    __mv_vop1708 = _mm256_loadu_pd(&y[((i0 + 0) + 343)]);
    __mv_vop1708 = _mm256_fmadd_pd(__mv_vop498, __mv_vop499, __mv_vop1708);
    _mm256_storeu_pd(&y[((i0 + 0) + 343)], __mv_vop1708);
    __mv_vop1709 = _mm256_loadu_pd(&y[((i0 + 4) + 343)]);
    __mv_vop1709 = _mm256_fmadd_pd(__mv_vop501, __mv_vop502, __mv_vop1709);
    _mm256_storeu_pd(&y[((i0 + 4) + 343)], __mv_vop1709);
    // y[1 * i0 + 343] += A[i0 + 664] * x[1 * i0 + 344];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 343] += A[i0 + 664] * x[1 * i0 + 344];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop504 = _mm256_loadu_pd(&A[((i0 + 0) + 672)]);
    __mv_vop505 = _mm256_loadu_pd(&x[((i0 + 0) + 343)]);
    __mv_vop507 = _mm256_loadu_pd(&A[((i0 + 4) + 672)]);
    __mv_vop508 = _mm256_loadu_pd(&x[((i0 + 4) + 343)]);
    __mv_vop1710 = _mm256_loadu_pd(&y[((i0 + 0) + 344)]);
    __mv_vop1710 = _mm256_fmadd_pd(__mv_vop504, __mv_vop505, __mv_vop1710);
    _mm256_storeu_pd(&y[((i0 + 0) + 344)], __mv_vop1710);
    __mv_vop1711 = _mm256_loadu_pd(&y[((i0 + 4) + 344)]);
    __mv_vop1711 = _mm256_fmadd_pd(__mv_vop507, __mv_vop508, __mv_vop1711);
    _mm256_storeu_pd(&y[((i0 + 4) + 344)], __mv_vop1711);
    // y[1 * i0 + 344] += A[i0 + 672] * x[1 * i0 + 343];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 344] += A[i0 + 672] * x[1 * i0 + 343];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop510 = _mm256_loadu_pd(&A[((i0 + 0) + 680)]);
    __mv_vop511 = _mm256_loadu_pd(&x[((i0 + 0) + 352)]);
    __mv_vop513 = _mm256_loadu_pd(&A[((i0 + 4) + 680)]);
    __mv_vop514 = _mm256_loadu_pd(&x[((i0 + 4) + 352)]);
    __mv_vop1712 = _mm256_loadu_pd(&y[((i0 + 0) + 351)]);
    __mv_vop1712 = _mm256_fmadd_pd(__mv_vop510, __mv_vop511, __mv_vop1712);
    _mm256_storeu_pd(&y[((i0 + 0) + 351)], __mv_vop1712);
    __mv_vop1713 = _mm256_loadu_pd(&y[((i0 + 4) + 351)]);
    __mv_vop1713 = _mm256_fmadd_pd(__mv_vop513, __mv_vop514, __mv_vop1713);
    _mm256_storeu_pd(&y[((i0 + 4) + 351)], __mv_vop1713);
    // y[1 * i0 + 351] += A[i0 + 680] * x[1 * i0 + 352];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 351] += A[i0 + 680] * x[1 * i0 + 352];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop516 = _mm256_loadu_pd(&A[((i0 + 0) + 688)]);
    __mv_vop517 = _mm256_loadu_pd(&x[((i0 + 0) + 351)]);
    __mv_vop519 = _mm256_loadu_pd(&A[((i0 + 4) + 688)]);
    __mv_vop520 = _mm256_loadu_pd(&x[((i0 + 4) + 351)]);
    __mv_vop1714 = _mm256_loadu_pd(&y[((i0 + 0) + 352)]);
    __mv_vop1714 = _mm256_fmadd_pd(__mv_vop516, __mv_vop517, __mv_vop1714);
    _mm256_storeu_pd(&y[((i0 + 0) + 352)], __mv_vop1714);
    __mv_vop1715 = _mm256_loadu_pd(&y[((i0 + 4) + 352)]);
    __mv_vop1715 = _mm256_fmadd_pd(__mv_vop519, __mv_vop520, __mv_vop1715);
    _mm256_storeu_pd(&y[((i0 + 4) + 352)], __mv_vop1715);
    // y[1 * i0 + 352] += A[i0 + 688] * x[1 * i0 + 351];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 352] += A[i0 + 688] * x[1 * i0 + 351];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop522 = _mm256_loadu_pd(&A[((i0 + 0) + 696)]);
    __mv_vop523 = _mm256_loadu_pd(&x[((i0 + 0) + 360)]);
    __mv_vop525 = _mm256_loadu_pd(&A[((i0 + 4) + 696)]);
    __mv_vop526 = _mm256_loadu_pd(&x[((i0 + 4) + 360)]);
    __mv_vop1716 = _mm256_loadu_pd(&y[((i0 + 0) + 359)]);
    __mv_vop1716 = _mm256_fmadd_pd(__mv_vop522, __mv_vop523, __mv_vop1716);
    _mm256_storeu_pd(&y[((i0 + 0) + 359)], __mv_vop1716);
    __mv_vop1717 = _mm256_loadu_pd(&y[((i0 + 4) + 359)]);
    __mv_vop1717 = _mm256_fmadd_pd(__mv_vop525, __mv_vop526, __mv_vop1717);
    _mm256_storeu_pd(&y[((i0 + 4) + 359)], __mv_vop1717);
    // y[1 * i0 + 359] += A[i0 + 696] * x[1 * i0 + 360];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 359] += A[i0 + 696] * x[1 * i0 + 360];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop528 = _mm256_loadu_pd(&A[((i0 + 0) + 704)]);
    __mv_vop529 = _mm256_loadu_pd(&x[((i0 + 0) + 359)]);
    __mv_vop531 = _mm256_loadu_pd(&A[((i0 + 4) + 704)]);
    __mv_vop532 = _mm256_loadu_pd(&x[((i0 + 4) + 359)]);
    __mv_vop1718 = _mm256_loadu_pd(&y[((i0 + 0) + 360)]);
    __mv_vop1718 = _mm256_fmadd_pd(__mv_vop528, __mv_vop529, __mv_vop1718);
    _mm256_storeu_pd(&y[((i0 + 0) + 360)], __mv_vop1718);
    __mv_vop1719 = _mm256_loadu_pd(&y[((i0 + 4) + 360)]);
    __mv_vop1719 = _mm256_fmadd_pd(__mv_vop531, __mv_vop532, __mv_vop1719);
    _mm256_storeu_pd(&y[((i0 + 4) + 360)], __mv_vop1719);
    // y[1 * i0 + 360] += A[i0 + 704] * x[1 * i0 + 359];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 360] += A[i0 + 704] * x[1 * i0 + 359];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop534 = _mm256_loadu_pd(&A[((i0 + 0) + 712)]);
    __mv_vop535 = _mm256_loadu_pd(&x[((i0 + 0) + 368)]);
    __mv_vop537 = _mm256_loadu_pd(&A[((i0 + 4) + 712)]);
    __mv_vop538 = _mm256_loadu_pd(&x[((i0 + 4) + 368)]);
    __mv_vop1720 = _mm256_loadu_pd(&y[((i0 + 0) + 367)]);
    __mv_vop1720 = _mm256_fmadd_pd(__mv_vop534, __mv_vop535, __mv_vop1720);
    _mm256_storeu_pd(&y[((i0 + 0) + 367)], __mv_vop1720);
    __mv_vop1721 = _mm256_loadu_pd(&y[((i0 + 4) + 367)]);
    __mv_vop1721 = _mm256_fmadd_pd(__mv_vop537, __mv_vop538, __mv_vop1721);
    _mm256_storeu_pd(&y[((i0 + 4) + 367)], __mv_vop1721);
    // y[1 * i0 + 367] += A[i0 + 712] * x[1 * i0 + 368];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 367] += A[i0 + 712] * x[1 * i0 + 368];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop540 = _mm256_loadu_pd(&A[((i0 + 0) + 720)]);
    __mv_vop541 = _mm256_loadu_pd(&x[((i0 + 0) + 367)]);
    __mv_vop543 = _mm256_loadu_pd(&A[((i0 + 4) + 720)]);
    __mv_vop544 = _mm256_loadu_pd(&x[((i0 + 4) + 367)]);
    __mv_vop1722 = _mm256_loadu_pd(&y[((i0 + 0) + 368)]);
    __mv_vop1722 = _mm256_fmadd_pd(__mv_vop540, __mv_vop541, __mv_vop1722);
    _mm256_storeu_pd(&y[((i0 + 0) + 368)], __mv_vop1722);
    __mv_vop1723 = _mm256_loadu_pd(&y[((i0 + 4) + 368)]);
    __mv_vop1723 = _mm256_fmadd_pd(__mv_vop543, __mv_vop544, __mv_vop1723);
    _mm256_storeu_pd(&y[((i0 + 4) + 368)], __mv_vop1723);
    // y[1 * i0 + 368] += A[i0 + 720] * x[1 * i0 + 367];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 368] += A[i0 + 720] * x[1 * i0 + 367];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop546 = _mm256_loadu_pd(&A[((i0 + 0) + 728)]);
    __mv_vop547 = _mm256_loadu_pd(&x[((i0 + 0) + 376)]);
    __mv_vop549 = _mm256_loadu_pd(&A[((i0 + 4) + 728)]);
    __mv_vop550 = _mm256_loadu_pd(&x[((i0 + 4) + 376)]);
    __mv_vop1724 = _mm256_loadu_pd(&y[((i0 + 0) + 375)]);
    __mv_vop1724 = _mm256_fmadd_pd(__mv_vop546, __mv_vop547, __mv_vop1724);
    _mm256_storeu_pd(&y[((i0 + 0) + 375)], __mv_vop1724);
    __mv_vop1725 = _mm256_loadu_pd(&y[((i0 + 4) + 375)]);
    __mv_vop1725 = _mm256_fmadd_pd(__mv_vop549, __mv_vop550, __mv_vop1725);
    _mm256_storeu_pd(&y[((i0 + 4) + 375)], __mv_vop1725);
    // y[1 * i0 + 375] += A[i0 + 728] * x[1 * i0 + 376];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 375] += A[i0 + 728] * x[1 * i0 + 376];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop552 = _mm256_loadu_pd(&A[((i0 + 0) + 736)]);
    __mv_vop553 = _mm256_loadu_pd(&x[((i0 + 0) + 375)]);
    __mv_vop555 = _mm256_loadu_pd(&A[((i0 + 4) + 736)]);
    __mv_vop556 = _mm256_loadu_pd(&x[((i0 + 4) + 375)]);
    __mv_vop1726 = _mm256_loadu_pd(&y[((i0 + 0) + 376)]);
    __mv_vop1726 = _mm256_fmadd_pd(__mv_vop552, __mv_vop553, __mv_vop1726);
    _mm256_storeu_pd(&y[((i0 + 0) + 376)], __mv_vop1726);
    __mv_vop1727 = _mm256_loadu_pd(&y[((i0 + 4) + 376)]);
    __mv_vop1727 = _mm256_fmadd_pd(__mv_vop555, __mv_vop556, __mv_vop1727);
    _mm256_storeu_pd(&y[((i0 + 4) + 376)], __mv_vop1727);
    // y[1 * i0 + 376] += A[i0 + 736] * x[1 * i0 + 375];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 376] += A[i0 + 736] * x[1 * i0 + 375];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop558 = _mm256_loadu_pd(&A[((i0 + 0) + 744)]);
    __mv_vop559 = _mm256_loadu_pd(&x[((i0 + 0) + 384)]);
    __mv_vop561 = _mm256_loadu_pd(&A[((i0 + 4) + 744)]);
    __mv_vop562 = _mm256_loadu_pd(&x[((i0 + 4) + 384)]);
    __mv_vop1728 = _mm256_loadu_pd(&y[((i0 + 0) + 383)]);
    __mv_vop1728 = _mm256_fmadd_pd(__mv_vop558, __mv_vop559, __mv_vop1728);
    _mm256_storeu_pd(&y[((i0 + 0) + 383)], __mv_vop1728);
    __mv_vop1729 = _mm256_loadu_pd(&y[((i0 + 4) + 383)]);
    __mv_vop1729 = _mm256_fmadd_pd(__mv_vop561, __mv_vop562, __mv_vop1729);
    _mm256_storeu_pd(&y[((i0 + 4) + 383)], __mv_vop1729);
    // y[1 * i0 + 383] += A[i0 + 744] * x[1 * i0 + 384];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 383] += A[i0 + 744] * x[1 * i0 + 384];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop564 = _mm256_loadu_pd(&A[((i0 + 0) + 752)]);
    __mv_vop565 = _mm256_loadu_pd(&x[((i0 + 0) + 383)]);
    __mv_vop567 = _mm256_loadu_pd(&A[((i0 + 4) + 752)]);
    __mv_vop568 = _mm256_loadu_pd(&x[((i0 + 4) + 383)]);
    __mv_vop1730 = _mm256_loadu_pd(&y[((i0 + 0) + 384)]);
    __mv_vop1730 = _mm256_fmadd_pd(__mv_vop564, __mv_vop565, __mv_vop1730);
    _mm256_storeu_pd(&y[((i0 + 0) + 384)], __mv_vop1730);
    __mv_vop1731 = _mm256_loadu_pd(&y[((i0 + 4) + 384)]);
    __mv_vop1731 = _mm256_fmadd_pd(__mv_vop567, __mv_vop568, __mv_vop1731);
    _mm256_storeu_pd(&y[((i0 + 4) + 384)], __mv_vop1731);
    // y[1 * i0 + 384] += A[i0 + 752] * x[1 * i0 + 383];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 384] += A[i0 + 752] * x[1 * i0 + 383];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop570 = _mm256_loadu_pd(&A[((i0 + 0) + 760)]);
    __mv_vop571 = _mm256_loadu_pd(&x[((i0 + 0) + 392)]);
    __mv_vop573 = _mm256_loadu_pd(&A[((i0 + 4) + 760)]);
    __mv_vop574 = _mm256_loadu_pd(&x[((i0 + 4) + 392)]);
    __mv_vop1732 = _mm256_loadu_pd(&y[((i0 + 0) + 391)]);
    __mv_vop1732 = _mm256_fmadd_pd(__mv_vop570, __mv_vop571, __mv_vop1732);
    _mm256_storeu_pd(&y[((i0 + 0) + 391)], __mv_vop1732);
    __mv_vop1733 = _mm256_loadu_pd(&y[((i0 + 4) + 391)]);
    __mv_vop1733 = _mm256_fmadd_pd(__mv_vop573, __mv_vop574, __mv_vop1733);
    _mm256_storeu_pd(&y[((i0 + 4) + 391)], __mv_vop1733);
    // y[1 * i0 + 391] += A[i0 + 760] * x[1 * i0 + 392];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 391] += A[i0 + 760] * x[1 * i0 + 392];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop576 = _mm256_loadu_pd(&A[((i0 + 0) + 768)]);
    __mv_vop577 = _mm256_loadu_pd(&x[((i0 + 0) + 391)]);
    __mv_vop579 = _mm256_loadu_pd(&A[((i0 + 4) + 768)]);
    __mv_vop580 = _mm256_loadu_pd(&x[((i0 + 4) + 391)]);
    __mv_vop1734 = _mm256_loadu_pd(&y[((i0 + 0) + 392)]);
    __mv_vop1734 = _mm256_fmadd_pd(__mv_vop576, __mv_vop577, __mv_vop1734);
    _mm256_storeu_pd(&y[((i0 + 0) + 392)], __mv_vop1734);
    __mv_vop1735 = _mm256_loadu_pd(&y[((i0 + 4) + 392)]);
    __mv_vop1735 = _mm256_fmadd_pd(__mv_vop579, __mv_vop580, __mv_vop1735);
    _mm256_storeu_pd(&y[((i0 + 4) + 392)], __mv_vop1735);
    // y[1 * i0 + 392] += A[i0 + 768] * x[1 * i0 + 391];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 392] += A[i0 + 768] * x[1 * i0 + 391];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop582 = _mm256_loadu_pd(&A[((i0 + 0) + 776)]);
    __mv_vop583 = _mm256_loadu_pd(&x[((i0 + 0) + 400)]);
    __mv_vop585 = _mm256_loadu_pd(&A[((i0 + 4) + 776)]);
    __mv_vop586 = _mm256_loadu_pd(&x[((i0 + 4) + 400)]);
    __mv_vop1736 = _mm256_loadu_pd(&y[((i0 + 0) + 399)]);
    __mv_vop1736 = _mm256_fmadd_pd(__mv_vop582, __mv_vop583, __mv_vop1736);
    _mm256_storeu_pd(&y[((i0 + 0) + 399)], __mv_vop1736);
    __mv_vop1737 = _mm256_loadu_pd(&y[((i0 + 4) + 399)]);
    __mv_vop1737 = _mm256_fmadd_pd(__mv_vop585, __mv_vop586, __mv_vop1737);
    _mm256_storeu_pd(&y[((i0 + 4) + 399)], __mv_vop1737);
    // y[1 * i0 + 399] += A[i0 + 776] * x[1 * i0 + 400];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 399] += A[i0 + 776] * x[1 * i0 + 400];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop588 = _mm256_loadu_pd(&A[((i0 + 0) + 784)]);
    __mv_vop589 = _mm256_loadu_pd(&x[((i0 + 0) + 399)]);
    __mv_vop591 = _mm256_loadu_pd(&A[((i0 + 4) + 784)]);
    __mv_vop592 = _mm256_loadu_pd(&x[((i0 + 4) + 399)]);
    __mv_vop1738 = _mm256_loadu_pd(&y[((i0 + 0) + 400)]);
    __mv_vop1738 = _mm256_fmadd_pd(__mv_vop588, __mv_vop589, __mv_vop1738);
    _mm256_storeu_pd(&y[((i0 + 0) + 400)], __mv_vop1738);
    __mv_vop1739 = _mm256_loadu_pd(&y[((i0 + 4) + 400)]);
    __mv_vop1739 = _mm256_fmadd_pd(__mv_vop591, __mv_vop592, __mv_vop1739);
    _mm256_storeu_pd(&y[((i0 + 4) + 400)], __mv_vop1739);
    // y[1 * i0 + 400] += A[i0 + 784] * x[1 * i0 + 399];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 400] += A[i0 + 784] * x[1 * i0 + 399];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop594 = _mm256_loadu_pd(&A[((i0 + 0) + 792)]);
    __mv_vop595 = _mm256_loadu_pd(&x[((i0 + 0) + 408)]);
    __mv_vop597 = _mm256_loadu_pd(&A[((i0 + 4) + 792)]);
    __mv_vop598 = _mm256_loadu_pd(&x[((i0 + 4) + 408)]);
    __mv_vop1740 = _mm256_loadu_pd(&y[((i0 + 0) + 407)]);
    __mv_vop1740 = _mm256_fmadd_pd(__mv_vop594, __mv_vop595, __mv_vop1740);
    _mm256_storeu_pd(&y[((i0 + 0) + 407)], __mv_vop1740);
    __mv_vop1741 = _mm256_loadu_pd(&y[((i0 + 4) + 407)]);
    __mv_vop1741 = _mm256_fmadd_pd(__mv_vop597, __mv_vop598, __mv_vop1741);
    _mm256_storeu_pd(&y[((i0 + 4) + 407)], __mv_vop1741);
    // y[1 * i0 + 407] += A[i0 + 792] * x[1 * i0 + 408];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 407] += A[i0 + 792] * x[1 * i0 + 408];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop600 = _mm256_loadu_pd(&A[((i0 + 0) + 800)]);
    __mv_vop601 = _mm256_loadu_pd(&x[((i0 + 0) + 407)]);
    __mv_vop603 = _mm256_loadu_pd(&A[((i0 + 4) + 800)]);
    __mv_vop604 = _mm256_loadu_pd(&x[((i0 + 4) + 407)]);
    __mv_vop1742 = _mm256_loadu_pd(&y[((i0 + 0) + 408)]);
    __mv_vop1742 = _mm256_fmadd_pd(__mv_vop600, __mv_vop601, __mv_vop1742);
    _mm256_storeu_pd(&y[((i0 + 0) + 408)], __mv_vop1742);
    __mv_vop1743 = _mm256_loadu_pd(&y[((i0 + 4) + 408)]);
    __mv_vop1743 = _mm256_fmadd_pd(__mv_vop603, __mv_vop604, __mv_vop1743);
    _mm256_storeu_pd(&y[((i0 + 4) + 408)], __mv_vop1743);
    // y[1 * i0 + 408] += A[i0 + 800] * x[1 * i0 + 407];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 408] += A[i0 + 800] * x[1 * i0 + 407];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop606 = _mm256_loadu_pd(&A[((i0 + 0) + 808)]);
    __mv_vop607 = _mm256_loadu_pd(&x[((i0 + 0) + 416)]);
    __mv_vop609 = _mm256_loadu_pd(&A[((i0 + 4) + 808)]);
    __mv_vop610 = _mm256_loadu_pd(&x[((i0 + 4) + 416)]);
    __mv_vop1744 = _mm256_loadu_pd(&y[((i0 + 0) + 415)]);
    __mv_vop1744 = _mm256_fmadd_pd(__mv_vop606, __mv_vop607, __mv_vop1744);
    _mm256_storeu_pd(&y[((i0 + 0) + 415)], __mv_vop1744);
    __mv_vop1745 = _mm256_loadu_pd(&y[((i0 + 4) + 415)]);
    __mv_vop1745 = _mm256_fmadd_pd(__mv_vop609, __mv_vop610, __mv_vop1745);
    _mm256_storeu_pd(&y[((i0 + 4) + 415)], __mv_vop1745);
    // y[1 * i0 + 415] += A[i0 + 808] * x[1 * i0 + 416];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 415] += A[i0 + 808] * x[1 * i0 + 416];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop612 = _mm256_loadu_pd(&A[((i0 + 0) + 816)]);
    __mv_vop613 = _mm256_loadu_pd(&x[((i0 + 0) + 415)]);
    __mv_vop615 = _mm256_loadu_pd(&A[((i0 + 4) + 816)]);
    __mv_vop616 = _mm256_loadu_pd(&x[((i0 + 4) + 415)]);
    __mv_vop1746 = _mm256_loadu_pd(&y[((i0 + 0) + 416)]);
    __mv_vop1746 = _mm256_fmadd_pd(__mv_vop612, __mv_vop613, __mv_vop1746);
    _mm256_storeu_pd(&y[((i0 + 0) + 416)], __mv_vop1746);
    __mv_vop1747 = _mm256_loadu_pd(&y[((i0 + 4) + 416)]);
    __mv_vop1747 = _mm256_fmadd_pd(__mv_vop615, __mv_vop616, __mv_vop1747);
    _mm256_storeu_pd(&y[((i0 + 4) + 416)], __mv_vop1747);
    // y[1 * i0 + 416] += A[i0 + 816] * x[1 * i0 + 415];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 416] += A[i0 + 816] * x[1 * i0 + 415];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop618 = _mm256_loadu_pd(&A[((i0 + 0) + 824)]);
    __mv_vop619 = _mm256_loadu_pd(&x[((i0 + 0) + 424)]);
    __mv_vop621 = _mm256_loadu_pd(&A[((i0 + 4) + 824)]);
    __mv_vop622 = _mm256_loadu_pd(&x[((i0 + 4) + 424)]);
    __mv_vop1748 = _mm256_loadu_pd(&y[((i0 + 0) + 423)]);
    __mv_vop1748 = _mm256_fmadd_pd(__mv_vop618, __mv_vop619, __mv_vop1748);
    _mm256_storeu_pd(&y[((i0 + 0) + 423)], __mv_vop1748);
    __mv_vop1749 = _mm256_loadu_pd(&y[((i0 + 4) + 423)]);
    __mv_vop1749 = _mm256_fmadd_pd(__mv_vop621, __mv_vop622, __mv_vop1749);
    _mm256_storeu_pd(&y[((i0 + 4) + 423)], __mv_vop1749);
    // y[1 * i0 + 423] += A[i0 + 824] * x[1 * i0 + 424];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 423] += A[i0 + 824] * x[1 * i0 + 424];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop624 = _mm256_loadu_pd(&A[((i0 + 0) + 832)]);
    __mv_vop625 = _mm256_loadu_pd(&x[((i0 + 0) + 423)]);
    __mv_vop627 = _mm256_loadu_pd(&A[((i0 + 4) + 832)]);
    __mv_vop628 = _mm256_loadu_pd(&x[((i0 + 4) + 423)]);
    __mv_vop1750 = _mm256_loadu_pd(&y[((i0 + 0) + 424)]);
    __mv_vop1750 = _mm256_fmadd_pd(__mv_vop624, __mv_vop625, __mv_vop1750);
    _mm256_storeu_pd(&y[((i0 + 0) + 424)], __mv_vop1750);
    __mv_vop1751 = _mm256_loadu_pd(&y[((i0 + 4) + 424)]);
    __mv_vop1751 = _mm256_fmadd_pd(__mv_vop627, __mv_vop628, __mv_vop1751);
    _mm256_storeu_pd(&y[((i0 + 4) + 424)], __mv_vop1751);
    // y[1 * i0 + 424] += A[i0 + 832] * x[1 * i0 + 423];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 424] += A[i0 + 832] * x[1 * i0 + 423];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop630 = _mm256_loadu_pd(&A[((i0 + 0) + 840)]);
    __mv_vop631 = _mm256_loadu_pd(&x[((i0 + 0) + 432)]);
    __mv_vop633 = _mm256_loadu_pd(&A[((i0 + 4) + 840)]);
    __mv_vop634 = _mm256_loadu_pd(&x[((i0 + 4) + 432)]);
    __mv_vop1752 = _mm256_loadu_pd(&y[((i0 + 0) + 431)]);
    __mv_vop1752 = _mm256_fmadd_pd(__mv_vop630, __mv_vop631, __mv_vop1752);
    _mm256_storeu_pd(&y[((i0 + 0) + 431)], __mv_vop1752);
    __mv_vop1753 = _mm256_loadu_pd(&y[((i0 + 4) + 431)]);
    __mv_vop1753 = _mm256_fmadd_pd(__mv_vop633, __mv_vop634, __mv_vop1753);
    _mm256_storeu_pd(&y[((i0 + 4) + 431)], __mv_vop1753);
    // y[1 * i0 + 431] += A[i0 + 840] * x[1 * i0 + 432];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 431] += A[i0 + 840] * x[1 * i0 + 432];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop636 = _mm256_loadu_pd(&A[((i0 + 0) + 848)]);
    __mv_vop637 = _mm256_loadu_pd(&x[((i0 + 0) + 431)]);
    __mv_vop639 = _mm256_loadu_pd(&A[((i0 + 4) + 848)]);
    __mv_vop640 = _mm256_loadu_pd(&x[((i0 + 4) + 431)]);
    __mv_vop1754 = _mm256_loadu_pd(&y[((i0 + 0) + 432)]);
    __mv_vop1754 = _mm256_fmadd_pd(__mv_vop636, __mv_vop637, __mv_vop1754);
    _mm256_storeu_pd(&y[((i0 + 0) + 432)], __mv_vop1754);
    __mv_vop1755 = _mm256_loadu_pd(&y[((i0 + 4) + 432)]);
    __mv_vop1755 = _mm256_fmadd_pd(__mv_vop639, __mv_vop640, __mv_vop1755);
    _mm256_storeu_pd(&y[((i0 + 4) + 432)], __mv_vop1755);
    // y[1 * i0 + 432] += A[i0 + 848] * x[1 * i0 + 431];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 432] += A[i0 + 848] * x[1 * i0 + 431];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop642 = _mm256_loadu_pd(&A[((i0 + 0) + 856)]);
    __mv_vop643 = _mm256_loadu_pd(&x[((i0 + 0) + 440)]);
    __mv_vop645 = _mm256_loadu_pd(&A[((i0 + 4) + 856)]);
    __mv_vop646 = _mm256_loadu_pd(&x[((i0 + 4) + 440)]);
    __mv_vop1756 = _mm256_loadu_pd(&y[((i0 + 0) + 439)]);
    __mv_vop1756 = _mm256_fmadd_pd(__mv_vop642, __mv_vop643, __mv_vop1756);
    _mm256_storeu_pd(&y[((i0 + 0) + 439)], __mv_vop1756);
    __mv_vop1757 = _mm256_loadu_pd(&y[((i0 + 4) + 439)]);
    __mv_vop1757 = _mm256_fmadd_pd(__mv_vop645, __mv_vop646, __mv_vop1757);
    _mm256_storeu_pd(&y[((i0 + 4) + 439)], __mv_vop1757);
    // y[1 * i0 + 439] += A[i0 + 856] * x[1 * i0 + 440];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 439] += A[i0 + 856] * x[1 * i0 + 440];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop648 = _mm256_loadu_pd(&A[((i0 + 0) + 864)]);
    __mv_vop649 = _mm256_loadu_pd(&x[((i0 + 0) + 439)]);
    __mv_vop651 = _mm256_loadu_pd(&A[((i0 + 4) + 864)]);
    __mv_vop652 = _mm256_loadu_pd(&x[((i0 + 4) + 439)]);
    __mv_vop1758 = _mm256_loadu_pd(&y[((i0 + 0) + 440)]);
    __mv_vop1758 = _mm256_fmadd_pd(__mv_vop648, __mv_vop649, __mv_vop1758);
    _mm256_storeu_pd(&y[((i0 + 0) + 440)], __mv_vop1758);
    __mv_vop1759 = _mm256_loadu_pd(&y[((i0 + 4) + 440)]);
    __mv_vop1759 = _mm256_fmadd_pd(__mv_vop651, __mv_vop652, __mv_vop1759);
    _mm256_storeu_pd(&y[((i0 + 4) + 440)], __mv_vop1759);
    // y[1 * i0 + 440] += A[i0 + 864] * x[1 * i0 + 439];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 440] += A[i0 + 864] * x[1 * i0 + 439];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop654 = _mm256_loadu_pd(&A[((i0 + 0) + 872)]);
    __mv_vop655 = _mm256_loadu_pd(&x[((i0 + 0) + 448)]);
    __mv_vop657 = _mm256_loadu_pd(&A[((i0 + 4) + 872)]);
    __mv_vop658 = _mm256_loadu_pd(&x[((i0 + 4) + 448)]);
    __mv_vop1760 = _mm256_loadu_pd(&y[((i0 + 0) + 447)]);
    __mv_vop1760 = _mm256_fmadd_pd(__mv_vop654, __mv_vop655, __mv_vop1760);
    _mm256_storeu_pd(&y[((i0 + 0) + 447)], __mv_vop1760);
    __mv_vop1761 = _mm256_loadu_pd(&y[((i0 + 4) + 447)]);
    __mv_vop1761 = _mm256_fmadd_pd(__mv_vop657, __mv_vop658, __mv_vop1761);
    _mm256_storeu_pd(&y[((i0 + 4) + 447)], __mv_vop1761);
    // y[1 * i0 + 447] += A[i0 + 872] * x[1 * i0 + 448];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 447] += A[i0 + 872] * x[1 * i0 + 448];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop660 = _mm256_loadu_pd(&A[((i0 + 0) + 880)]);
    __mv_vop661 = _mm256_loadu_pd(&x[((i0 + 0) + 447)]);
    __mv_vop663 = _mm256_loadu_pd(&A[((i0 + 4) + 880)]);
    __mv_vop664 = _mm256_loadu_pd(&x[((i0 + 4) + 447)]);
    __mv_vop1762 = _mm256_loadu_pd(&y[((i0 + 0) + 448)]);
    __mv_vop1762 = _mm256_fmadd_pd(__mv_vop660, __mv_vop661, __mv_vop1762);
    _mm256_storeu_pd(&y[((i0 + 0) + 448)], __mv_vop1762);
    __mv_vop1763 = _mm256_loadu_pd(&y[((i0 + 4) + 448)]);
    __mv_vop1763 = _mm256_fmadd_pd(__mv_vop663, __mv_vop664, __mv_vop1763);
    _mm256_storeu_pd(&y[((i0 + 4) + 448)], __mv_vop1763);
    // y[1 * i0 + 448] += A[i0 + 880] * x[1 * i0 + 447];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 448] += A[i0 + 880] * x[1 * i0 + 447];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop666 = _mm256_loadu_pd(&A[((i0 + 0) + 888)]);
    __mv_vop667 = _mm256_loadu_pd(&x[((i0 + 0) + 456)]);
    __mv_vop669 = _mm256_loadu_pd(&A[((i0 + 4) + 888)]);
    __mv_vop670 = _mm256_loadu_pd(&x[((i0 + 4) + 456)]);
    __mv_vop1764 = _mm256_loadu_pd(&y[((i0 + 0) + 455)]);
    __mv_vop1764 = _mm256_fmadd_pd(__mv_vop666, __mv_vop667, __mv_vop1764);
    _mm256_storeu_pd(&y[((i0 + 0) + 455)], __mv_vop1764);
    __mv_vop1765 = _mm256_loadu_pd(&y[((i0 + 4) + 455)]);
    __mv_vop1765 = _mm256_fmadd_pd(__mv_vop669, __mv_vop670, __mv_vop1765);
    _mm256_storeu_pd(&y[((i0 + 4) + 455)], __mv_vop1765);
    // y[1 * i0 + 455] += A[i0 + 888] * x[1 * i0 + 456];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 455] += A[i0 + 888] * x[1 * i0 + 456];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop672 = _mm256_loadu_pd(&A[((i0 + 0) + 896)]);
    __mv_vop673 = _mm256_loadu_pd(&x[((i0 + 0) + 455)]);
    __mv_vop675 = _mm256_loadu_pd(&A[((i0 + 4) + 896)]);
    __mv_vop676 = _mm256_loadu_pd(&x[((i0 + 4) + 455)]);
    __mv_vop1766 = _mm256_loadu_pd(&y[((i0 + 0) + 456)]);
    __mv_vop1766 = _mm256_fmadd_pd(__mv_vop672, __mv_vop673, __mv_vop1766);
    _mm256_storeu_pd(&y[((i0 + 0) + 456)], __mv_vop1766);
    __mv_vop1767 = _mm256_loadu_pd(&y[((i0 + 4) + 456)]);
    __mv_vop1767 = _mm256_fmadd_pd(__mv_vop675, __mv_vop676, __mv_vop1767);
    _mm256_storeu_pd(&y[((i0 + 4) + 456)], __mv_vop1767);
    // y[1 * i0 + 456] += A[i0 + 896] * x[1 * i0 + 455];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 456] += A[i0 + 896] * x[1 * i0 + 455];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop678 = _mm256_loadu_pd(&A[((i0 + 0) + 904)]);
    __mv_vop679 = _mm256_loadu_pd(&x[((i0 + 0) + 464)]);
    __mv_vop681 = _mm256_loadu_pd(&A[((i0 + 4) + 904)]);
    __mv_vop682 = _mm256_loadu_pd(&x[((i0 + 4) + 464)]);
    __mv_vop1768 = _mm256_loadu_pd(&y[((i0 + 0) + 463)]);
    __mv_vop1768 = _mm256_fmadd_pd(__mv_vop678, __mv_vop679, __mv_vop1768);
    _mm256_storeu_pd(&y[((i0 + 0) + 463)], __mv_vop1768);
    __mv_vop1769 = _mm256_loadu_pd(&y[((i0 + 4) + 463)]);
    __mv_vop1769 = _mm256_fmadd_pd(__mv_vop681, __mv_vop682, __mv_vop1769);
    _mm256_storeu_pd(&y[((i0 + 4) + 463)], __mv_vop1769);
    // y[1 * i0 + 463] += A[i0 + 904] * x[1 * i0 + 464];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 463] += A[i0 + 904] * x[1 * i0 + 464];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop684 = _mm256_loadu_pd(&A[((i0 + 0) + 912)]);
    __mv_vop685 = _mm256_loadu_pd(&x[((i0 + 0) + 463)]);
    __mv_vop687 = _mm256_loadu_pd(&A[((i0 + 4) + 912)]);
    __mv_vop688 = _mm256_loadu_pd(&x[((i0 + 4) + 463)]);
    __mv_vop1770 = _mm256_loadu_pd(&y[((i0 + 0) + 464)]);
    __mv_vop1770 = _mm256_fmadd_pd(__mv_vop684, __mv_vop685, __mv_vop1770);
    _mm256_storeu_pd(&y[((i0 + 0) + 464)], __mv_vop1770);
    __mv_vop1771 = _mm256_loadu_pd(&y[((i0 + 4) + 464)]);
    __mv_vop1771 = _mm256_fmadd_pd(__mv_vop687, __mv_vop688, __mv_vop1771);
    _mm256_storeu_pd(&y[((i0 + 4) + 464)], __mv_vop1771);
    // y[1 * i0 + 464] += A[i0 + 912] * x[1 * i0 + 463];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 464] += A[i0 + 912] * x[1 * i0 + 463];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop690 = _mm256_loadu_pd(&A[((i0 + 0) + 920)]);
    __mv_vop691 = _mm256_loadu_pd(&x[((i0 + 0) + 472)]);
    __mv_vop693 = _mm256_loadu_pd(&A[((i0 + 4) + 920)]);
    __mv_vop694 = _mm256_loadu_pd(&x[((i0 + 4) + 472)]);
    __mv_vop1772 = _mm256_loadu_pd(&y[((i0 + 0) + 471)]);
    __mv_vop1772 = _mm256_fmadd_pd(__mv_vop690, __mv_vop691, __mv_vop1772);
    _mm256_storeu_pd(&y[((i0 + 0) + 471)], __mv_vop1772);
    __mv_vop1773 = _mm256_loadu_pd(&y[((i0 + 4) + 471)]);
    __mv_vop1773 = _mm256_fmadd_pd(__mv_vop693, __mv_vop694, __mv_vop1773);
    _mm256_storeu_pd(&y[((i0 + 4) + 471)], __mv_vop1773);
    // y[1 * i0 + 471] += A[i0 + 920] * x[1 * i0 + 472];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 471] += A[i0 + 920] * x[1 * i0 + 472];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop696 = _mm256_loadu_pd(&A[((i0 + 0) + 928)]);
    __mv_vop697 = _mm256_loadu_pd(&x[((i0 + 0) + 471)]);
    __mv_vop699 = _mm256_loadu_pd(&A[((i0 + 4) + 928)]);
    __mv_vop700 = _mm256_loadu_pd(&x[((i0 + 4) + 471)]);
    __mv_vop1774 = _mm256_loadu_pd(&y[((i0 + 0) + 472)]);
    __mv_vop1774 = _mm256_fmadd_pd(__mv_vop696, __mv_vop697, __mv_vop1774);
    _mm256_storeu_pd(&y[((i0 + 0) + 472)], __mv_vop1774);
    __mv_vop1775 = _mm256_loadu_pd(&y[((i0 + 4) + 472)]);
    __mv_vop1775 = _mm256_fmadd_pd(__mv_vop699, __mv_vop700, __mv_vop1775);
    _mm256_storeu_pd(&y[((i0 + 4) + 472)], __mv_vop1775);
    // y[1 * i0 + 472] += A[i0 + 928] * x[1 * i0 + 471];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 472] += A[i0 + 928] * x[1 * i0 + 471];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop702 = _mm256_loadu_pd(&A[((i0 + 0) + 936)]);
    __mv_vop703 = _mm256_loadu_pd(&x[((i0 + 0) + 480)]);
    __mv_vop705 = _mm256_loadu_pd(&A[((i0 + 4) + 936)]);
    __mv_vop706 = _mm256_loadu_pd(&x[((i0 + 4) + 480)]);
    __mv_vop1776 = _mm256_loadu_pd(&y[((i0 + 0) + 479)]);
    __mv_vop1776 = _mm256_fmadd_pd(__mv_vop702, __mv_vop703, __mv_vop1776);
    _mm256_storeu_pd(&y[((i0 + 0) + 479)], __mv_vop1776);
    __mv_vop1777 = _mm256_loadu_pd(&y[((i0 + 4) + 479)]);
    __mv_vop1777 = _mm256_fmadd_pd(__mv_vop705, __mv_vop706, __mv_vop1777);
    _mm256_storeu_pd(&y[((i0 + 4) + 479)], __mv_vop1777);
    // y[1 * i0 + 479] += A[i0 + 936] * x[1 * i0 + 480];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 479] += A[i0 + 936] * x[1 * i0 + 480];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop708 = _mm256_loadu_pd(&A[((i0 + 0) + 944)]);
    __mv_vop709 = _mm256_loadu_pd(&x[((i0 + 0) + 479)]);
    __mv_vop711 = _mm256_loadu_pd(&A[((i0 + 4) + 944)]);
    __mv_vop712 = _mm256_loadu_pd(&x[((i0 + 4) + 479)]);
    __mv_vop1778 = _mm256_loadu_pd(&y[((i0 + 0) + 480)]);
    __mv_vop1778 = _mm256_fmadd_pd(__mv_vop708, __mv_vop709, __mv_vop1778);
    _mm256_storeu_pd(&y[((i0 + 0) + 480)], __mv_vop1778);
    __mv_vop1779 = _mm256_loadu_pd(&y[((i0 + 4) + 480)]);
    __mv_vop1779 = _mm256_fmadd_pd(__mv_vop711, __mv_vop712, __mv_vop1779);
    _mm256_storeu_pd(&y[((i0 + 4) + 480)], __mv_vop1779);
    // y[1 * i0 + 480] += A[i0 + 944] * x[1 * i0 + 479];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 480] += A[i0 + 944] * x[1 * i0 + 479];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop714 = _mm256_loadu_pd(&A[((i0 + 0) + 952)]);
    __mv_vop715 = _mm256_loadu_pd(&x[((i0 + 0) + 496)]);
    __mv_vop717 = _mm256_loadu_pd(&A[((i0 + 4) + 952)]);
    __mv_vop718 = _mm256_loadu_pd(&x[((i0 + 4) + 496)]);
    __mv_vop1780 = _mm256_loadu_pd(&y[((i0 + 0) + 495)]);
    __mv_vop1780 = _mm256_fmadd_pd(__mv_vop714, __mv_vop715, __mv_vop1780);
    _mm256_storeu_pd(&y[((i0 + 0) + 495)], __mv_vop1780);
    __mv_vop1781 = _mm256_loadu_pd(&y[((i0 + 4) + 495)]);
    __mv_vop1781 = _mm256_fmadd_pd(__mv_vop717, __mv_vop718, __mv_vop1781);
    _mm256_storeu_pd(&y[((i0 + 4) + 495)], __mv_vop1781);
    // y[1 * i0 + 495] += A[i0 + 952] * x[1 * i0 + 496];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 495] += A[i0 + 952] * x[1 * i0 + 496];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop720 = _mm256_loadu_pd(&A[((i0 + 0) + 960)]);
    __mv_vop721 = _mm256_loadu_pd(&x[((i0 + 0) + 495)]);
    __mv_vop723 = _mm256_loadu_pd(&A[((i0 + 4) + 960)]);
    __mv_vop724 = _mm256_loadu_pd(&x[((i0 + 4) + 495)]);
    __mv_vop1782 = _mm256_loadu_pd(&y[((i0 + 0) + 496)]);
    __mv_vop1782 = _mm256_fmadd_pd(__mv_vop720, __mv_vop721, __mv_vop1782);
    _mm256_storeu_pd(&y[((i0 + 0) + 496)], __mv_vop1782);
    __mv_vop1783 = _mm256_loadu_pd(&y[((i0 + 4) + 496)]);
    __mv_vop1783 = _mm256_fmadd_pd(__mv_vop723, __mv_vop724, __mv_vop1783);
    _mm256_storeu_pd(&y[((i0 + 4) + 496)], __mv_vop1783);
    // y[1 * i0 + 496] += A[i0 + 960] * x[1 * i0 + 495];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 496] += A[i0 + 960] * x[1 * i0 + 495];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop726 = _mm256_loadu_pd(&A[((i0 + 0) + 968)]);
    __mv_vop727 = _mm256_loadu_pd(&x[((i0 + 0) + 504)]);
    __mv_vop729 = _mm256_loadu_pd(&A[((i0 + 4) + 968)]);
    __mv_vop730 = _mm256_loadu_pd(&x[((i0 + 4) + 504)]);
    __mv_vop1784 = _mm256_loadu_pd(&y[((i0 + 0) + 503)]);
    __mv_vop1784 = _mm256_fmadd_pd(__mv_vop726, __mv_vop727, __mv_vop1784);
    _mm256_storeu_pd(&y[((i0 + 0) + 503)], __mv_vop1784);
    __mv_vop1785 = _mm256_loadu_pd(&y[((i0 + 4) + 503)]);
    __mv_vop1785 = _mm256_fmadd_pd(__mv_vop729, __mv_vop730, __mv_vop1785);
    _mm256_storeu_pd(&y[((i0 + 4) + 503)], __mv_vop1785);
    // y[1 * i0 + 503] += A[i0 + 968] * x[1 * i0 + 504];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 503] += A[i0 + 968] * x[1 * i0 + 504];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop732 = _mm256_loadu_pd(&A[((i0 + 0) + 976)]);
    __mv_vop733 = _mm256_loadu_pd(&x[((i0 + 0) + 503)]);
    __mv_vop735 = _mm256_loadu_pd(&A[((i0 + 4) + 976)]);
    __mv_vop736 = _mm256_loadu_pd(&x[((i0 + 4) + 503)]);
    __mv_vop1786 = _mm256_loadu_pd(&y[((i0 + 0) + 504)]);
    __mv_vop1786 = _mm256_fmadd_pd(__mv_vop732, __mv_vop733, __mv_vop1786);
    _mm256_storeu_pd(&y[((i0 + 0) + 504)], __mv_vop1786);
    __mv_vop1787 = _mm256_loadu_pd(&y[((i0 + 4) + 504)]);
    __mv_vop1787 = _mm256_fmadd_pd(__mv_vop735, __mv_vop736, __mv_vop1787);
    _mm256_storeu_pd(&y[((i0 + 4) + 504)], __mv_vop1787);
    // y[1 * i0 + 504] += A[i0 + 976] * x[1 * i0 + 503];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 504] += A[i0 + 976] * x[1 * i0 + 503];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop738 = _mm256_loadu_pd(&A[((i0 + 0) + 984)]);
    __mv_vop739 = _mm256_loadu_pd(&x[((i0 + 0) + 512)]);
    __mv_vop741 = _mm256_loadu_pd(&A[((i0 + 4) + 984)]);
    __mv_vop742 = _mm256_loadu_pd(&x[((i0 + 4) + 512)]);
    __mv_vop1788 = _mm256_loadu_pd(&y[((i0 + 0) + 511)]);
    __mv_vop1788 = _mm256_fmadd_pd(__mv_vop738, __mv_vop739, __mv_vop1788);
    _mm256_storeu_pd(&y[((i0 + 0) + 511)], __mv_vop1788);
    __mv_vop1789 = _mm256_loadu_pd(&y[((i0 + 4) + 511)]);
    __mv_vop1789 = _mm256_fmadd_pd(__mv_vop741, __mv_vop742, __mv_vop1789);
    _mm256_storeu_pd(&y[((i0 + 4) + 511)], __mv_vop1789);
    // y[1 * i0 + 511] += A[i0 + 984] * x[1 * i0 + 512];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 511] += A[i0 + 984] * x[1 * i0 + 512];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop744 = _mm256_loadu_pd(&A[((i0 + 0) + 992)]);
    __mv_vop745 = _mm256_loadu_pd(&x[((i0 + 0) + 511)]);
    __mv_vop747 = _mm256_loadu_pd(&A[((i0 + 4) + 992)]);
    __mv_vop748 = _mm256_loadu_pd(&x[((i0 + 4) + 511)]);
    __mv_vop1790 = _mm256_loadu_pd(&y[((i0 + 0) + 512)]);
    __mv_vop1790 = _mm256_fmadd_pd(__mv_vop744, __mv_vop745, __mv_vop1790);
    _mm256_storeu_pd(&y[((i0 + 0) + 512)], __mv_vop1790);
    __mv_vop1791 = _mm256_loadu_pd(&y[((i0 + 4) + 512)]);
    __mv_vop1791 = _mm256_fmadd_pd(__mv_vop747, __mv_vop748, __mv_vop1791);
    _mm256_storeu_pd(&y[((i0 + 4) + 512)], __mv_vop1791);
    // y[1 * i0 + 512] += A[i0 + 992] * x[1 * i0 + 511];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 512] += A[i0 + 992] * x[1 * i0 + 511];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop750 = _mm256_loadu_pd(&A[((i0 + 0) + 1000)]);
    __mv_vop751 = _mm256_loadu_pd(&x[((i0 + 0) + 520)]);
    __mv_vop753 = _mm256_loadu_pd(&A[((i0 + 4) + 1000)]);
    __mv_vop754 = _mm256_loadu_pd(&x[((i0 + 4) + 520)]);
    __mv_vop1792 = _mm256_loadu_pd(&y[((i0 + 0) + 519)]);
    __mv_vop1792 = _mm256_fmadd_pd(__mv_vop750, __mv_vop751, __mv_vop1792);
    _mm256_storeu_pd(&y[((i0 + 0) + 519)], __mv_vop1792);
    __mv_vop1793 = _mm256_loadu_pd(&y[((i0 + 4) + 519)]);
    __mv_vop1793 = _mm256_fmadd_pd(__mv_vop753, __mv_vop754, __mv_vop1793);
    _mm256_storeu_pd(&y[((i0 + 4) + 519)], __mv_vop1793);
    // y[1 * i0 + 519] += A[i0 + 1000] * x[1 * i0 + 520];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 519] += A[i0 + 1000] * x[1 * i0 + 520];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop756 = _mm256_loadu_pd(&A[((i0 + 0) + 1008)]);
    __mv_vop757 = _mm256_loadu_pd(&x[((i0 + 0) + 519)]);
    __mv_vop759 = _mm256_loadu_pd(&A[((i0 + 4) + 1008)]);
    __mv_vop760 = _mm256_loadu_pd(&x[((i0 + 4) + 519)]);
    __mv_vop1794 = _mm256_loadu_pd(&y[((i0 + 0) + 520)]);
    __mv_vop1794 = _mm256_fmadd_pd(__mv_vop756, __mv_vop757, __mv_vop1794);
    _mm256_storeu_pd(&y[((i0 + 0) + 520)], __mv_vop1794);
    __mv_vop1795 = _mm256_loadu_pd(&y[((i0 + 4) + 520)]);
    __mv_vop1795 = _mm256_fmadd_pd(__mv_vop759, __mv_vop760, __mv_vop1795);
    _mm256_storeu_pd(&y[((i0 + 4) + 520)], __mv_vop1795);
    // y[1 * i0 + 520] += A[i0 + 1008] * x[1 * i0 + 519];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 520] += A[i0 + 1008] * x[1 * i0 + 519];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop762 = _mm256_loadu_pd(&A[((i0 + 0) + 1016)]);
    __mv_vop763 = _mm256_loadu_pd(&x[((i0 + 0) + 528)]);
    __mv_vop765 = _mm256_loadu_pd(&A[((i0 + 4) + 1016)]);
    __mv_vop766 = _mm256_loadu_pd(&x[((i0 + 4) + 528)]);
    __mv_vop1796 = _mm256_loadu_pd(&y[((i0 + 0) + 527)]);
    __mv_vop1796 = _mm256_fmadd_pd(__mv_vop762, __mv_vop763, __mv_vop1796);
    _mm256_storeu_pd(&y[((i0 + 0) + 527)], __mv_vop1796);
    __mv_vop1797 = _mm256_loadu_pd(&y[((i0 + 4) + 527)]);
    __mv_vop1797 = _mm256_fmadd_pd(__mv_vop765, __mv_vop766, __mv_vop1797);
    _mm256_storeu_pd(&y[((i0 + 4) + 527)], __mv_vop1797);
    // y[1 * i0 + 527] += A[i0 + 1016] * x[1 * i0 + 528];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 527] += A[i0 + 1016] * x[1 * i0 + 528];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop768 = _mm256_loadu_pd(&A[((i0 + 0) + 1024)]);
    __mv_vop769 = _mm256_loadu_pd(&x[((i0 + 0) + 527)]);
    __mv_vop771 = _mm256_loadu_pd(&A[((i0 + 4) + 1024)]);
    __mv_vop772 = _mm256_loadu_pd(&x[((i0 + 4) + 527)]);
    __mv_vop1798 = _mm256_loadu_pd(&y[((i0 + 0) + 528)]);
    __mv_vop1798 = _mm256_fmadd_pd(__mv_vop768, __mv_vop769, __mv_vop1798);
    _mm256_storeu_pd(&y[((i0 + 0) + 528)], __mv_vop1798);
    __mv_vop1799 = _mm256_loadu_pd(&y[((i0 + 4) + 528)]);
    __mv_vop1799 = _mm256_fmadd_pd(__mv_vop771, __mv_vop772, __mv_vop1799);
    _mm256_storeu_pd(&y[((i0 + 4) + 528)], __mv_vop1799);
    // y[1 * i0 + 528] += A[i0 + 1024] * x[1 * i0 + 527];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 528] += A[i0 + 1024] * x[1 * i0 + 527];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop774 = _mm256_loadu_pd(&A[((i0 + 0) + 1032)]);
    __mv_vop775 = _mm256_loadu_pd(&x[((i0 + 0) + 536)]);
    __mv_vop777 = _mm256_loadu_pd(&A[((i0 + 4) + 1032)]);
    __mv_vop778 = _mm256_loadu_pd(&x[((i0 + 4) + 536)]);
    __mv_vop1800 = _mm256_loadu_pd(&y[((i0 + 0) + 535)]);
    __mv_vop1800 = _mm256_fmadd_pd(__mv_vop774, __mv_vop775, __mv_vop1800);
    _mm256_storeu_pd(&y[((i0 + 0) + 535)], __mv_vop1800);
    __mv_vop1801 = _mm256_loadu_pd(&y[((i0 + 4) + 535)]);
    __mv_vop1801 = _mm256_fmadd_pd(__mv_vop777, __mv_vop778, __mv_vop1801);
    _mm256_storeu_pd(&y[((i0 + 4) + 535)], __mv_vop1801);
    // y[1 * i0 + 535] += A[i0 + 1032] * x[1 * i0 + 536];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 535] += A[i0 + 1032] * x[1 * i0 + 536];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop780 = _mm256_loadu_pd(&A[((i0 + 0) + 1040)]);
    __mv_vop781 = _mm256_loadu_pd(&x[((i0 + 0) + 535)]);
    __mv_vop783 = _mm256_loadu_pd(&A[((i0 + 4) + 1040)]);
    __mv_vop784 = _mm256_loadu_pd(&x[((i0 + 4) + 535)]);
    __mv_vop1802 = _mm256_loadu_pd(&y[((i0 + 0) + 536)]);
    __mv_vop1802 = _mm256_fmadd_pd(__mv_vop780, __mv_vop781, __mv_vop1802);
    _mm256_storeu_pd(&y[((i0 + 0) + 536)], __mv_vop1802);
    __mv_vop1803 = _mm256_loadu_pd(&y[((i0 + 4) + 536)]);
    __mv_vop1803 = _mm256_fmadd_pd(__mv_vop783, __mv_vop784, __mv_vop1803);
    _mm256_storeu_pd(&y[((i0 + 4) + 536)], __mv_vop1803);
    // y[1 * i0 + 536] += A[i0 + 1040] * x[1 * i0 + 535];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 536] += A[i0 + 1040] * x[1 * i0 + 535];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop786 = _mm256_loadu_pd(&A[((i0 + 0) + 1048)]);
    __mv_vop787 = _mm256_loadu_pd(&x[((i0 + 0) + 544)]);
    __mv_vop789 = _mm256_loadu_pd(&A[((i0 + 4) + 1048)]);
    __mv_vop790 = _mm256_loadu_pd(&x[((i0 + 4) + 544)]);
    __mv_vop1804 = _mm256_loadu_pd(&y[((i0 + 0) + 543)]);
    __mv_vop1804 = _mm256_fmadd_pd(__mv_vop786, __mv_vop787, __mv_vop1804);
    _mm256_storeu_pd(&y[((i0 + 0) + 543)], __mv_vop1804);
    __mv_vop1805 = _mm256_loadu_pd(&y[((i0 + 4) + 543)]);
    __mv_vop1805 = _mm256_fmadd_pd(__mv_vop789, __mv_vop790, __mv_vop1805);
    _mm256_storeu_pd(&y[((i0 + 4) + 543)], __mv_vop1805);
    // y[1 * i0 + 543] += A[i0 + 1048] * x[1 * i0 + 544];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 543] += A[i0 + 1048] * x[1 * i0 + 544];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop792 = _mm256_loadu_pd(&A[((i0 + 0) + 1056)]);
    __mv_vop793 = _mm256_loadu_pd(&x[((i0 + 0) + 543)]);
    __mv_vop795 = _mm256_loadu_pd(&A[((i0 + 4) + 1056)]);
    __mv_vop796 = _mm256_loadu_pd(&x[((i0 + 4) + 543)]);
    __mv_vop1806 = _mm256_loadu_pd(&y[((i0 + 0) + 544)]);
    __mv_vop1806 = _mm256_fmadd_pd(__mv_vop792, __mv_vop793, __mv_vop1806);
    _mm256_storeu_pd(&y[((i0 + 0) + 544)], __mv_vop1806);
    __mv_vop1807 = _mm256_loadu_pd(&y[((i0 + 4) + 544)]);
    __mv_vop1807 = _mm256_fmadd_pd(__mv_vop795, __mv_vop796, __mv_vop1807);
    _mm256_storeu_pd(&y[((i0 + 4) + 544)], __mv_vop1807);
    // y[1 * i0 + 544] += A[i0 + 1056] * x[1 * i0 + 543];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 544] += A[i0 + 1056] * x[1 * i0 + 543];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop798 = _mm256_loadu_pd(&A[((i0 + 0) + 1064)]);
    __mv_vop799 = _mm256_loadu_pd(&x[((i0 + 0) + 552)]);
    __mv_vop801 = _mm256_loadu_pd(&A[((i0 + 4) + 1064)]);
    __mv_vop802 = _mm256_loadu_pd(&x[((i0 + 4) + 552)]);
    __mv_vop1808 = _mm256_loadu_pd(&y[((i0 + 0) + 551)]);
    __mv_vop1808 = _mm256_fmadd_pd(__mv_vop798, __mv_vop799, __mv_vop1808);
    _mm256_storeu_pd(&y[((i0 + 0) + 551)], __mv_vop1808);
    __mv_vop1809 = _mm256_loadu_pd(&y[((i0 + 4) + 551)]);
    __mv_vop1809 = _mm256_fmadd_pd(__mv_vop801, __mv_vop802, __mv_vop1809);
    _mm256_storeu_pd(&y[((i0 + 4) + 551)], __mv_vop1809);
    // y[1 * i0 + 551] += A[i0 + 1064] * x[1 * i0 + 552];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 551] += A[i0 + 1064] * x[1 * i0 + 552];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop804 = _mm256_loadu_pd(&A[((i0 + 0) + 1072)]);
    __mv_vop805 = _mm256_loadu_pd(&x[((i0 + 0) + 551)]);
    __mv_vop807 = _mm256_loadu_pd(&A[((i0 + 4) + 1072)]);
    __mv_vop808 = _mm256_loadu_pd(&x[((i0 + 4) + 551)]);
    __mv_vop1810 = _mm256_loadu_pd(&y[((i0 + 0) + 552)]);
    __mv_vop1810 = _mm256_fmadd_pd(__mv_vop804, __mv_vop805, __mv_vop1810);
    _mm256_storeu_pd(&y[((i0 + 0) + 552)], __mv_vop1810);
    __mv_vop1811 = _mm256_loadu_pd(&y[((i0 + 4) + 552)]);
    __mv_vop1811 = _mm256_fmadd_pd(__mv_vop807, __mv_vop808, __mv_vop1811);
    _mm256_storeu_pd(&y[((i0 + 4) + 552)], __mv_vop1811);
    // y[1 * i0 + 552] += A[i0 + 1072] * x[1 * i0 + 551];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 552] += A[i0 + 1072] * x[1 * i0 + 551];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop810 = _mm256_loadu_pd(&A[((i0 + 0) + 1080)]);
    __mv_vop811 = _mm256_loadu_pd(&x[((i0 + 0) + 560)]);
    __mv_vop813 = _mm256_loadu_pd(&A[((i0 + 4) + 1080)]);
    __mv_vop814 = _mm256_loadu_pd(&x[((i0 + 4) + 560)]);
    __mv_vop1812 = _mm256_loadu_pd(&y[((i0 + 0) + 559)]);
    __mv_vop1812 = _mm256_fmadd_pd(__mv_vop810, __mv_vop811, __mv_vop1812);
    _mm256_storeu_pd(&y[((i0 + 0) + 559)], __mv_vop1812);
    __mv_vop1813 = _mm256_loadu_pd(&y[((i0 + 4) + 559)]);
    __mv_vop1813 = _mm256_fmadd_pd(__mv_vop813, __mv_vop814, __mv_vop1813);
    _mm256_storeu_pd(&y[((i0 + 4) + 559)], __mv_vop1813);
    // y[1 * i0 + 559] += A[i0 + 1080] * x[1 * i0 + 560];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 559] += A[i0 + 1080] * x[1 * i0 + 560];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop816 = _mm256_loadu_pd(&A[((i0 + 0) + 1088)]);
    __mv_vop817 = _mm256_loadu_pd(&x[((i0 + 0) + 559)]);
    __mv_vop819 = _mm256_loadu_pd(&A[((i0 + 4) + 1088)]);
    __mv_vop820 = _mm256_loadu_pd(&x[((i0 + 4) + 559)]);
    __mv_vop1814 = _mm256_loadu_pd(&y[((i0 + 0) + 560)]);
    __mv_vop1814 = _mm256_fmadd_pd(__mv_vop816, __mv_vop817, __mv_vop1814);
    _mm256_storeu_pd(&y[((i0 + 0) + 560)], __mv_vop1814);
    __mv_vop1815 = _mm256_loadu_pd(&y[((i0 + 4) + 560)]);
    __mv_vop1815 = _mm256_fmadd_pd(__mv_vop819, __mv_vop820, __mv_vop1815);
    _mm256_storeu_pd(&y[((i0 + 4) + 560)], __mv_vop1815);
    // y[1 * i0 + 560] += A[i0 + 1088] * x[1 * i0 + 559];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 560] += A[i0 + 1088] * x[1 * i0 + 559];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop822 = _mm256_loadu_pd(&A[((i0 + 0) + 1096)]);
    __mv_vop823 = _mm256_loadu_pd(&x[((i0 + 0) + 568)]);
    __mv_vop825 = _mm256_loadu_pd(&A[((i0 + 4) + 1096)]);
    __mv_vop826 = _mm256_loadu_pd(&x[((i0 + 4) + 568)]);
    __mv_vop1816 = _mm256_loadu_pd(&y[((i0 + 0) + 567)]);
    __mv_vop1816 = _mm256_fmadd_pd(__mv_vop822, __mv_vop823, __mv_vop1816);
    _mm256_storeu_pd(&y[((i0 + 0) + 567)], __mv_vop1816);
    __mv_vop1817 = _mm256_loadu_pd(&y[((i0 + 4) + 567)]);
    __mv_vop1817 = _mm256_fmadd_pd(__mv_vop825, __mv_vop826, __mv_vop1817);
    _mm256_storeu_pd(&y[((i0 + 4) + 567)], __mv_vop1817);
    // y[1 * i0 + 567] += A[i0 + 1096] * x[1 * i0 + 568];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 567] += A[i0 + 1096] * x[1 * i0 + 568];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop828 = _mm256_loadu_pd(&A[((i0 + 0) + 1104)]);
    __mv_vop829 = _mm256_loadu_pd(&x[((i0 + 0) + 567)]);
    __mv_vop831 = _mm256_loadu_pd(&A[((i0 + 4) + 1104)]);
    __mv_vop832 = _mm256_loadu_pd(&x[((i0 + 4) + 567)]);
    __mv_vop1818 = _mm256_loadu_pd(&y[((i0 + 0) + 568)]);
    __mv_vop1818 = _mm256_fmadd_pd(__mv_vop828, __mv_vop829, __mv_vop1818);
    _mm256_storeu_pd(&y[((i0 + 0) + 568)], __mv_vop1818);
    __mv_vop1819 = _mm256_loadu_pd(&y[((i0 + 4) + 568)]);
    __mv_vop1819 = _mm256_fmadd_pd(__mv_vop831, __mv_vop832, __mv_vop1819);
    _mm256_storeu_pd(&y[((i0 + 4) + 568)], __mv_vop1819);
    // y[1 * i0 + 568] += A[i0 + 1104] * x[1 * i0 + 567];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 568] += A[i0 + 1104] * x[1 * i0 + 567];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop834 = _mm256_loadu_pd(&A[((i0 + 0) + 1112)]);
    __mv_vop835 = _mm256_loadu_pd(&x[((i0 + 0) + 576)]);
    __mv_vop837 = _mm256_loadu_pd(&A[((i0 + 4) + 1112)]);
    __mv_vop838 = _mm256_loadu_pd(&x[((i0 + 4) + 576)]);
    __mv_vop1820 = _mm256_loadu_pd(&y[((i0 + 0) + 575)]);
    __mv_vop1820 = _mm256_fmadd_pd(__mv_vop834, __mv_vop835, __mv_vop1820);
    _mm256_storeu_pd(&y[((i0 + 0) + 575)], __mv_vop1820);
    __mv_vop1821 = _mm256_loadu_pd(&y[((i0 + 4) + 575)]);
    __mv_vop1821 = _mm256_fmadd_pd(__mv_vop837, __mv_vop838, __mv_vop1821);
    _mm256_storeu_pd(&y[((i0 + 4) + 575)], __mv_vop1821);
    // y[1 * i0 + 575] += A[i0 + 1112] * x[1 * i0 + 576];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 575] += A[i0 + 1112] * x[1 * i0 + 576];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop840 = _mm256_loadu_pd(&A[((i0 + 0) + 1120)]);
    __mv_vop841 = _mm256_loadu_pd(&x[((i0 + 0) + 575)]);
    __mv_vop843 = _mm256_loadu_pd(&A[((i0 + 4) + 1120)]);
    __mv_vop844 = _mm256_loadu_pd(&x[((i0 + 4) + 575)]);
    __mv_vop1822 = _mm256_loadu_pd(&y[((i0 + 0) + 576)]);
    __mv_vop1822 = _mm256_fmadd_pd(__mv_vop840, __mv_vop841, __mv_vop1822);
    _mm256_storeu_pd(&y[((i0 + 0) + 576)], __mv_vop1822);
    __mv_vop1823 = _mm256_loadu_pd(&y[((i0 + 4) + 576)]);
    __mv_vop1823 = _mm256_fmadd_pd(__mv_vop843, __mv_vop844, __mv_vop1823);
    _mm256_storeu_pd(&y[((i0 + 4) + 576)], __mv_vop1823);
    // y[1 * i0 + 576] += A[i0 + 1120] * x[1 * i0 + 575];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 576] += A[i0 + 1120] * x[1 * i0 + 575];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop846 = _mm256_loadu_pd(&A[((i0 + 0) + 1128)]);
    __mv_vop847 = _mm256_loadu_pd(&x[((i0 + 0) + 584)]);
    __mv_vop849 = _mm256_loadu_pd(&A[((i0 + 4) + 1128)]);
    __mv_vop850 = _mm256_loadu_pd(&x[((i0 + 4) + 584)]);
    __mv_vop1824 = _mm256_loadu_pd(&y[((i0 + 0) + 583)]);
    __mv_vop1824 = _mm256_fmadd_pd(__mv_vop846, __mv_vop847, __mv_vop1824);
    _mm256_storeu_pd(&y[((i0 + 0) + 583)], __mv_vop1824);
    __mv_vop1825 = _mm256_loadu_pd(&y[((i0 + 4) + 583)]);
    __mv_vop1825 = _mm256_fmadd_pd(__mv_vop849, __mv_vop850, __mv_vop1825);
    _mm256_storeu_pd(&y[((i0 + 4) + 583)], __mv_vop1825);
    // y[1 * i0 + 583] += A[i0 + 1128] * x[1 * i0 + 584];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 583] += A[i0 + 1128] * x[1 * i0 + 584];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop852 = _mm256_loadu_pd(&A[((i0 + 0) + 1136)]);
    __mv_vop853 = _mm256_loadu_pd(&x[((i0 + 0) + 583)]);
    __mv_vop855 = _mm256_loadu_pd(&A[((i0 + 4) + 1136)]);
    __mv_vop856 = _mm256_loadu_pd(&x[((i0 + 4) + 583)]);
    __mv_vop1826 = _mm256_loadu_pd(&y[((i0 + 0) + 584)]);
    __mv_vop1826 = _mm256_fmadd_pd(__mv_vop852, __mv_vop853, __mv_vop1826);
    _mm256_storeu_pd(&y[((i0 + 0) + 584)], __mv_vop1826);
    __mv_vop1827 = _mm256_loadu_pd(&y[((i0 + 4) + 584)]);
    __mv_vop1827 = _mm256_fmadd_pd(__mv_vop855, __mv_vop856, __mv_vop1827);
    _mm256_storeu_pd(&y[((i0 + 4) + 584)], __mv_vop1827);
    // y[1 * i0 + 584] += A[i0 + 1136] * x[1 * i0 + 583];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 584] += A[i0 + 1136] * x[1 * i0 + 583];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop858 = _mm256_loadu_pd(&A[((i0 + 0) + 1144)]);
    __mv_vop859 = _mm256_loadu_pd(&x[((i0 + 0) + 592)]);
    __mv_vop861 = _mm256_loadu_pd(&A[((i0 + 4) + 1144)]);
    __mv_vop862 = _mm256_loadu_pd(&x[((i0 + 4) + 592)]);
    __mv_vop1828 = _mm256_loadu_pd(&y[((i0 + 0) + 591)]);
    __mv_vop1828 = _mm256_fmadd_pd(__mv_vop858, __mv_vop859, __mv_vop1828);
    _mm256_storeu_pd(&y[((i0 + 0) + 591)], __mv_vop1828);
    __mv_vop1829 = _mm256_loadu_pd(&y[((i0 + 4) + 591)]);
    __mv_vop1829 = _mm256_fmadd_pd(__mv_vop861, __mv_vop862, __mv_vop1829);
    _mm256_storeu_pd(&y[((i0 + 4) + 591)], __mv_vop1829);
    // y[1 * i0 + 591] += A[i0 + 1144] * x[1 * i0 + 592];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 591] += A[i0 + 1144] * x[1 * i0 + 592];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop864 = _mm256_loadu_pd(&A[((i0 + 0) + 1152)]);
    __mv_vop865 = _mm256_loadu_pd(&x[((i0 + 0) + 591)]);
    __mv_vop867 = _mm256_loadu_pd(&A[((i0 + 4) + 1152)]);
    __mv_vop868 = _mm256_loadu_pd(&x[((i0 + 4) + 591)]);
    __mv_vop1830 = _mm256_loadu_pd(&y[((i0 + 0) + 592)]);
    __mv_vop1830 = _mm256_fmadd_pd(__mv_vop864, __mv_vop865, __mv_vop1830);
    _mm256_storeu_pd(&y[((i0 + 0) + 592)], __mv_vop1830);
    __mv_vop1831 = _mm256_loadu_pd(&y[((i0 + 4) + 592)]);
    __mv_vop1831 = _mm256_fmadd_pd(__mv_vop867, __mv_vop868, __mv_vop1831);
    _mm256_storeu_pd(&y[((i0 + 4) + 592)], __mv_vop1831);
    // y[1 * i0 + 592] += A[i0 + 1152] * x[1 * i0 + 591];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 592] += A[i0 + 1152] * x[1 * i0 + 591];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop870 = _mm256_loadu_pd(&A[((i0 + 0) + 1160)]);
    __mv_vop871 = _mm256_loadu_pd(&x[((i0 + 0) + 600)]);
    __mv_vop873 = _mm256_loadu_pd(&A[((i0 + 4) + 1160)]);
    __mv_vop874 = _mm256_loadu_pd(&x[((i0 + 4) + 600)]);
    __mv_vop1832 = _mm256_loadu_pd(&y[((i0 + 0) + 599)]);
    __mv_vop1832 = _mm256_fmadd_pd(__mv_vop870, __mv_vop871, __mv_vop1832);
    _mm256_storeu_pd(&y[((i0 + 0) + 599)], __mv_vop1832);
    __mv_vop1833 = _mm256_loadu_pd(&y[((i0 + 4) + 599)]);
    __mv_vop1833 = _mm256_fmadd_pd(__mv_vop873, __mv_vop874, __mv_vop1833);
    _mm256_storeu_pd(&y[((i0 + 4) + 599)], __mv_vop1833);
    // y[1 * i0 + 599] += A[i0 + 1160] * x[1 * i0 + 600];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 599] += A[i0 + 1160] * x[1 * i0 + 600];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop876 = _mm256_loadu_pd(&A[((i0 + 0) + 1168)]);
    __mv_vop877 = _mm256_loadu_pd(&x[((i0 + 0) + 599)]);
    __mv_vop879 = _mm256_loadu_pd(&A[((i0 + 4) + 1168)]);
    __mv_vop880 = _mm256_loadu_pd(&x[((i0 + 4) + 599)]);
    __mv_vop1834 = _mm256_loadu_pd(&y[((i0 + 0) + 600)]);
    __mv_vop1834 = _mm256_fmadd_pd(__mv_vop876, __mv_vop877, __mv_vop1834);
    _mm256_storeu_pd(&y[((i0 + 0) + 600)], __mv_vop1834);
    __mv_vop1835 = _mm256_loadu_pd(&y[((i0 + 4) + 600)]);
    __mv_vop1835 = _mm256_fmadd_pd(__mv_vop879, __mv_vop880, __mv_vop1835);
    _mm256_storeu_pd(&y[((i0 + 4) + 600)], __mv_vop1835);
    // y[1 * i0 + 600] += A[i0 + 1168] * x[1 * i0 + 599];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 600] += A[i0 + 1168] * x[1 * i0 + 599];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop882 = _mm256_loadu_pd(&A[((i0 + 0) + 1176)]);
    __mv_vop883 = _mm256_loadu_pd(&x[((i0 + 0) + 608)]);
    __mv_vop885 = _mm256_loadu_pd(&A[((i0 + 4) + 1176)]);
    __mv_vop886 = _mm256_loadu_pd(&x[((i0 + 4) + 608)]);
    __mv_vop1836 = _mm256_loadu_pd(&y[((i0 + 0) + 607)]);
    __mv_vop1836 = _mm256_fmadd_pd(__mv_vop882, __mv_vop883, __mv_vop1836);
    _mm256_storeu_pd(&y[((i0 + 0) + 607)], __mv_vop1836);
    __mv_vop1837 = _mm256_loadu_pd(&y[((i0 + 4) + 607)]);
    __mv_vop1837 = _mm256_fmadd_pd(__mv_vop885, __mv_vop886, __mv_vop1837);
    _mm256_storeu_pd(&y[((i0 + 4) + 607)], __mv_vop1837);
    // y[1 * i0 + 607] += A[i0 + 1176] * x[1 * i0 + 608];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 607] += A[i0 + 1176] * x[1 * i0 + 608];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop888 = _mm256_loadu_pd(&A[((i0 + 0) + 1184)]);
    __mv_vop889 = _mm256_loadu_pd(&x[((i0 + 0) + 607)]);
    __mv_vop891 = _mm256_loadu_pd(&A[((i0 + 4) + 1184)]);
    __mv_vop892 = _mm256_loadu_pd(&x[((i0 + 4) + 607)]);
    __mv_vop1838 = _mm256_loadu_pd(&y[((i0 + 0) + 608)]);
    __mv_vop1838 = _mm256_fmadd_pd(__mv_vop888, __mv_vop889, __mv_vop1838);
    _mm256_storeu_pd(&y[((i0 + 0) + 608)], __mv_vop1838);
    __mv_vop1839 = _mm256_loadu_pd(&y[((i0 + 4) + 608)]);
    __mv_vop1839 = _mm256_fmadd_pd(__mv_vop891, __mv_vop892, __mv_vop1839);
    _mm256_storeu_pd(&y[((i0 + 4) + 608)], __mv_vop1839);
    // y[1 * i0 + 608] += A[i0 + 1184] * x[1 * i0 + 607];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 608] += A[i0 + 1184] * x[1 * i0 + 607];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop894 = _mm256_loadu_pd(&A[((i0 + 0) + 1192)]);
    __mv_vop895 = _mm256_loadu_pd(&x[((i0 + 0) + 616)]);
    __mv_vop897 = _mm256_loadu_pd(&A[((i0 + 4) + 1192)]);
    __mv_vop898 = _mm256_loadu_pd(&x[((i0 + 4) + 616)]);
    __mv_vop1840 = _mm256_loadu_pd(&y[((i0 + 0) + 615)]);
    __mv_vop1840 = _mm256_fmadd_pd(__mv_vop894, __mv_vop895, __mv_vop1840);
    _mm256_storeu_pd(&y[((i0 + 0) + 615)], __mv_vop1840);
    __mv_vop1841 = _mm256_loadu_pd(&y[((i0 + 4) + 615)]);
    __mv_vop1841 = _mm256_fmadd_pd(__mv_vop897, __mv_vop898, __mv_vop1841);
    _mm256_storeu_pd(&y[((i0 + 4) + 615)], __mv_vop1841);
    // y[1 * i0 + 615] += A[i0 + 1192] * x[1 * i0 + 616];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 615] += A[i0 + 1192] * x[1 * i0 + 616];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop900 = _mm256_loadu_pd(&A[((i0 + 0) + 1200)]);
    __mv_vop901 = _mm256_loadu_pd(&x[((i0 + 0) + 615)]);
    __mv_vop903 = _mm256_loadu_pd(&A[((i0 + 4) + 1200)]);
    __mv_vop904 = _mm256_loadu_pd(&x[((i0 + 4) + 615)]);
    __mv_vop1842 = _mm256_loadu_pd(&y[((i0 + 0) + 616)]);
    __mv_vop1842 = _mm256_fmadd_pd(__mv_vop900, __mv_vop901, __mv_vop1842);
    _mm256_storeu_pd(&y[((i0 + 0) + 616)], __mv_vop1842);
    __mv_vop1843 = _mm256_loadu_pd(&y[((i0 + 4) + 616)]);
    __mv_vop1843 = _mm256_fmadd_pd(__mv_vop903, __mv_vop904, __mv_vop1843);
    _mm256_storeu_pd(&y[((i0 + 4) + 616)], __mv_vop1843);
    // y[1 * i0 + 616] += A[i0 + 1200] * x[1 * i0 + 615];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 616] += A[i0 + 1200] * x[1 * i0 + 615];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop906 = _mm256_loadu_pd(&A[((i0 + 0) + 1208)]);
    __mv_vop907 = _mm256_loadu_pd(&x[((i0 + 0) + 624)]);
    __mv_vop909 = _mm256_loadu_pd(&A[((i0 + 4) + 1208)]);
    __mv_vop910 = _mm256_loadu_pd(&x[((i0 + 4) + 624)]);
    __mv_vop1844 = _mm256_loadu_pd(&y[((i0 + 0) + 623)]);
    __mv_vop1844 = _mm256_fmadd_pd(__mv_vop906, __mv_vop907, __mv_vop1844);
    _mm256_storeu_pd(&y[((i0 + 0) + 623)], __mv_vop1844);
    __mv_vop1845 = _mm256_loadu_pd(&y[((i0 + 4) + 623)]);
    __mv_vop1845 = _mm256_fmadd_pd(__mv_vop909, __mv_vop910, __mv_vop1845);
    _mm256_storeu_pd(&y[((i0 + 4) + 623)], __mv_vop1845);
    // y[1 * i0 + 623] += A[i0 + 1208] * x[1 * i0 + 624];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 623] += A[i0 + 1208] * x[1 * i0 + 624];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop912 = _mm256_loadu_pd(&A[((i0 + 0) + 1216)]);
    __mv_vop913 = _mm256_loadu_pd(&x[((i0 + 0) + 623)]);
    __mv_vop915 = _mm256_loadu_pd(&A[((i0 + 4) + 1216)]);
    __mv_vop916 = _mm256_loadu_pd(&x[((i0 + 4) + 623)]);
    __mv_vop1846 = _mm256_loadu_pd(&y[((i0 + 0) + 624)]);
    __mv_vop1846 = _mm256_fmadd_pd(__mv_vop912, __mv_vop913, __mv_vop1846);
    _mm256_storeu_pd(&y[((i0 + 0) + 624)], __mv_vop1846);
    __mv_vop1847 = _mm256_loadu_pd(&y[((i0 + 4) + 624)]);
    __mv_vop1847 = _mm256_fmadd_pd(__mv_vop915, __mv_vop916, __mv_vop1847);
    _mm256_storeu_pd(&y[((i0 + 4) + 624)], __mv_vop1847);
    // y[1 * i0 + 624] += A[i0 + 1216] * x[1 * i0 + 623];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 624] += A[i0 + 1216] * x[1 * i0 + 623];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop918 = _mm256_loadu_pd(&A[((i0 + 0) + 1224)]);
    __mv_vop919 = _mm256_loadu_pd(&x[((i0 + 0) + 632)]);
    __mv_vop921 = _mm256_loadu_pd(&A[((i0 + 4) + 1224)]);
    __mv_vop922 = _mm256_loadu_pd(&x[((i0 + 4) + 632)]);
    __mv_vop1848 = _mm256_loadu_pd(&y[((i0 + 0) + 631)]);
    __mv_vop1848 = _mm256_fmadd_pd(__mv_vop918, __mv_vop919, __mv_vop1848);
    _mm256_storeu_pd(&y[((i0 + 0) + 631)], __mv_vop1848);
    __mv_vop1849 = _mm256_loadu_pd(&y[((i0 + 4) + 631)]);
    __mv_vop1849 = _mm256_fmadd_pd(__mv_vop921, __mv_vop922, __mv_vop1849);
    _mm256_storeu_pd(&y[((i0 + 4) + 631)], __mv_vop1849);
    // y[1 * i0 + 631] += A[i0 + 1224] * x[1 * i0 + 632];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 631] += A[i0 + 1224] * x[1 * i0 + 632];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop924 = _mm256_loadu_pd(&A[((i0 + 0) + 1232)]);
    __mv_vop925 = _mm256_loadu_pd(&x[((i0 + 0) + 631)]);
    __mv_vop927 = _mm256_loadu_pd(&A[((i0 + 4) + 1232)]);
    __mv_vop928 = _mm256_loadu_pd(&x[((i0 + 4) + 631)]);
    __mv_vop1850 = _mm256_loadu_pd(&y[((i0 + 0) + 632)]);
    __mv_vop1850 = _mm256_fmadd_pd(__mv_vop924, __mv_vop925, __mv_vop1850);
    _mm256_storeu_pd(&y[((i0 + 0) + 632)], __mv_vop1850);
    __mv_vop1851 = _mm256_loadu_pd(&y[((i0 + 4) + 632)]);
    __mv_vop1851 = _mm256_fmadd_pd(__mv_vop927, __mv_vop928, __mv_vop1851);
    _mm256_storeu_pd(&y[((i0 + 4) + 632)], __mv_vop1851);
    // y[1 * i0 + 632] += A[i0 + 1232] * x[1 * i0 + 631];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 632] += A[i0 + 1232] * x[1 * i0 + 631];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop930 = _mm256_loadu_pd(&A[((i0 + 0) + 1240)]);
    __mv_vop931 = _mm256_loadu_pd(&x[((i0 + 0) + 640)]);
    __mv_vop933 = _mm256_loadu_pd(&A[((i0 + 4) + 1240)]);
    __mv_vop934 = _mm256_loadu_pd(&x[((i0 + 4) + 640)]);
    __mv_vop1852 = _mm256_loadu_pd(&y[((i0 + 0) + 639)]);
    __mv_vop1852 = _mm256_fmadd_pd(__mv_vop930, __mv_vop931, __mv_vop1852);
    _mm256_storeu_pd(&y[((i0 + 0) + 639)], __mv_vop1852);
    __mv_vop1853 = _mm256_loadu_pd(&y[((i0 + 4) + 639)]);
    __mv_vop1853 = _mm256_fmadd_pd(__mv_vop933, __mv_vop934, __mv_vop1853);
    _mm256_storeu_pd(&y[((i0 + 4) + 639)], __mv_vop1853);
    // y[1 * i0 + 639] += A[i0 + 1240] * x[1 * i0 + 640];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 639] += A[i0 + 1240] * x[1 * i0 + 640];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop936 = _mm256_loadu_pd(&A[((i0 + 0) + 1248)]);
    __mv_vop937 = _mm256_loadu_pd(&x[((i0 + 0) + 639)]);
    __mv_vop939 = _mm256_loadu_pd(&A[((i0 + 4) + 1248)]);
    __mv_vop940 = _mm256_loadu_pd(&x[((i0 + 4) + 639)]);
    __mv_vop1854 = _mm256_loadu_pd(&y[((i0 + 0) + 640)]);
    __mv_vop1854 = _mm256_fmadd_pd(__mv_vop936, __mv_vop937, __mv_vop1854);
    _mm256_storeu_pd(&y[((i0 + 0) + 640)], __mv_vop1854);
    __mv_vop1855 = _mm256_loadu_pd(&y[((i0 + 4) + 640)]);
    __mv_vop1855 = _mm256_fmadd_pd(__mv_vop939, __mv_vop940, __mv_vop1855);
    _mm256_storeu_pd(&y[((i0 + 4) + 640)], __mv_vop1855);
    // y[1 * i0 + 640] += A[i0 + 1248] * x[1 * i0 + 639];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 640] += A[i0 + 1248] * x[1 * i0 + 639];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop942 = _mm256_loadu_pd(&A[((i0 + 0) + 1256)]);
    __mv_vop943 = _mm256_loadu_pd(&x[((i0 + 0) + 655)]);
    __mv_vop945 = _mm256_loadu_pd(&A[((i0 + 4) + 1256)]);
    __mv_vop946 = _mm256_loadu_pd(&x[((i0 + 4) + 655)]);
    __mv_vop1856 = _mm256_loadu_pd(&y[((i0 + 0) + 654)]);
    __mv_vop1856 = _mm256_fmadd_pd(__mv_vop942, __mv_vop943, __mv_vop1856);
    _mm256_storeu_pd(&y[((i0 + 0) + 654)], __mv_vop1856);
    __mv_vop1857 = _mm256_loadu_pd(&y[((i0 + 4) + 654)]);
    __mv_vop1857 = _mm256_fmadd_pd(__mv_vop945, __mv_vop946, __mv_vop1857);
    _mm256_storeu_pd(&y[((i0 + 4) + 654)], __mv_vop1857);
    // y[1 * i0 + 654] += A[i0 + 1256] * x[1 * i0 + 655];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 654] += A[i0 + 1256] * x[1 * i0 + 655];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop948 = _mm256_loadu_pd(&A[((i0 + 0) + 1264)]);
    __mv_vop949 = _mm256_loadu_pd(&x[((i0 + 0) + 654)]);
    __mv_vop951 = _mm256_loadu_pd(&A[((i0 + 4) + 1264)]);
    __mv_vop952 = _mm256_loadu_pd(&x[((i0 + 4) + 654)]);
    __mv_vop1858 = _mm256_loadu_pd(&y[((i0 + 0) + 655)]);
    __mv_vop1858 = _mm256_fmadd_pd(__mv_vop948, __mv_vop949, __mv_vop1858);
    _mm256_storeu_pd(&y[((i0 + 0) + 655)], __mv_vop1858);
    __mv_vop1859 = _mm256_loadu_pd(&y[((i0 + 4) + 655)]);
    __mv_vop1859 = _mm256_fmadd_pd(__mv_vop951, __mv_vop952, __mv_vop1859);
    _mm256_storeu_pd(&y[((i0 + 4) + 655)], __mv_vop1859);
    // y[1 * i0 + 655] += A[i0 + 1264] * x[1 * i0 + 654];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 655] += A[i0 + 1264] * x[1 * i0 + 654];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop954 = _mm256_loadu_pd(&A[((i0 + 0) + 1272)]);
    __mv_vop955 = _mm256_loadu_pd(&x[((i0 + 0) + 663)]);
    __mv_vop957 = _mm256_loadu_pd(&A[((i0 + 4) + 1272)]);
    __mv_vop958 = _mm256_loadu_pd(&x[((i0 + 4) + 663)]);
    __mv_vop1860 = _mm256_loadu_pd(&y[((i0 + 0) + 662)]);
    __mv_vop1860 = _mm256_fmadd_pd(__mv_vop954, __mv_vop955, __mv_vop1860);
    _mm256_storeu_pd(&y[((i0 + 0) + 662)], __mv_vop1860);
    __mv_vop1861 = _mm256_loadu_pd(&y[((i0 + 4) + 662)]);
    __mv_vop1861 = _mm256_fmadd_pd(__mv_vop957, __mv_vop958, __mv_vop1861);
    _mm256_storeu_pd(&y[((i0 + 4) + 662)], __mv_vop1861);
    // y[1 * i0 + 662] += A[i0 + 1272] * x[1 * i0 + 663];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 662] += A[i0 + 1272] * x[1 * i0 + 663];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop960 = _mm256_loadu_pd(&A[((i0 + 0) + 1280)]);
    __mv_vop961 = _mm256_loadu_pd(&x[((i0 + 0) + 662)]);
    __mv_vop963 = _mm256_loadu_pd(&A[((i0 + 4) + 1280)]);
    __mv_vop964 = _mm256_loadu_pd(&x[((i0 + 4) + 662)]);
    __mv_vop1862 = _mm256_loadu_pd(&y[((i0 + 0) + 663)]);
    __mv_vop1862 = _mm256_fmadd_pd(__mv_vop960, __mv_vop961, __mv_vop1862);
    _mm256_storeu_pd(&y[((i0 + 0) + 663)], __mv_vop1862);
    __mv_vop1863 = _mm256_loadu_pd(&y[((i0 + 4) + 663)]);
    __mv_vop1863 = _mm256_fmadd_pd(__mv_vop963, __mv_vop964, __mv_vop1863);
    _mm256_storeu_pd(&y[((i0 + 4) + 663)], __mv_vop1863);
    // y[1 * i0 + 663] += A[i0 + 1280] * x[1 * i0 + 662];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 663] += A[i0 + 1280] * x[1 * i0 + 662];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop966 = _mm256_loadu_pd(&A[((i0 + 0) + 1288)]);
    __mv_vop967 = _mm256_loadu_pd(&x[((i0 + 0) + 671)]);
    __mv_vop969 = _mm256_loadu_pd(&A[((i0 + 4) + 1288)]);
    __mv_vop970 = _mm256_loadu_pd(&x[((i0 + 4) + 671)]);
    __mv_vop1864 = _mm256_loadu_pd(&y[((i0 + 0) + 670)]);
    __mv_vop1864 = _mm256_fmadd_pd(__mv_vop966, __mv_vop967, __mv_vop1864);
    _mm256_storeu_pd(&y[((i0 + 0) + 670)], __mv_vop1864);
    __mv_vop1865 = _mm256_loadu_pd(&y[((i0 + 4) + 670)]);
    __mv_vop1865 = _mm256_fmadd_pd(__mv_vop969, __mv_vop970, __mv_vop1865);
    _mm256_storeu_pd(&y[((i0 + 4) + 670)], __mv_vop1865);
    // y[1 * i0 + 670] += A[i0 + 1288] * x[1 * i0 + 671];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 670] += A[i0 + 1288] * x[1 * i0 + 671];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop972 = _mm256_loadu_pd(&A[((i0 + 0) + 1296)]);
    __mv_vop973 = _mm256_loadu_pd(&x[((i0 + 0) + 670)]);
    __mv_vop975 = _mm256_loadu_pd(&A[((i0 + 4) + 1296)]);
    __mv_vop976 = _mm256_loadu_pd(&x[((i0 + 4) + 670)]);
    __mv_vop1866 = _mm256_loadu_pd(&y[((i0 + 0) + 671)]);
    __mv_vop1866 = _mm256_fmadd_pd(__mv_vop972, __mv_vop973, __mv_vop1866);
    _mm256_storeu_pd(&y[((i0 + 0) + 671)], __mv_vop1866);
    __mv_vop1867 = _mm256_loadu_pd(&y[((i0 + 4) + 671)]);
    __mv_vop1867 = _mm256_fmadd_pd(__mv_vop975, __mv_vop976, __mv_vop1867);
    _mm256_storeu_pd(&y[((i0 + 4) + 671)], __mv_vop1867);
    // y[1 * i0 + 671] += A[i0 + 1296] * x[1 * i0 + 670];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 671] += A[i0 + 1296] * x[1 * i0 + 670];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop978 = _mm256_loadu_pd(&A[((i0 + 0) + 1304)]);
    __mv_vop979 = _mm256_loadu_pd(&x[((i0 + 0) + 679)]);
    __mv_vop981 = _mm256_loadu_pd(&A[((i0 + 4) + 1304)]);
    __mv_vop982 = _mm256_loadu_pd(&x[((i0 + 4) + 679)]);
    __mv_vop1868 = _mm256_loadu_pd(&y[((i0 + 0) + 678)]);
    __mv_vop1868 = _mm256_fmadd_pd(__mv_vop978, __mv_vop979, __mv_vop1868);
    _mm256_storeu_pd(&y[((i0 + 0) + 678)], __mv_vop1868);
    __mv_vop1869 = _mm256_loadu_pd(&y[((i0 + 4) + 678)]);
    __mv_vop1869 = _mm256_fmadd_pd(__mv_vop981, __mv_vop982, __mv_vop1869);
    _mm256_storeu_pd(&y[((i0 + 4) + 678)], __mv_vop1869);
    // y[1 * i0 + 678] += A[i0 + 1304] * x[1 * i0 + 679];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 678] += A[i0 + 1304] * x[1 * i0 + 679];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop984 = _mm256_loadu_pd(&A[((i0 + 0) + 1312)]);
    __mv_vop985 = _mm256_loadu_pd(&x[((i0 + 0) + 678)]);
    __mv_vop987 = _mm256_loadu_pd(&A[((i0 + 4) + 1312)]);
    __mv_vop988 = _mm256_loadu_pd(&x[((i0 + 4) + 678)]);
    __mv_vop1870 = _mm256_loadu_pd(&y[((i0 + 0) + 679)]);
    __mv_vop1870 = _mm256_fmadd_pd(__mv_vop984, __mv_vop985, __mv_vop1870);
    _mm256_storeu_pd(&y[((i0 + 0) + 679)], __mv_vop1870);
    __mv_vop1871 = _mm256_loadu_pd(&y[((i0 + 4) + 679)]);
    __mv_vop1871 = _mm256_fmadd_pd(__mv_vop987, __mv_vop988, __mv_vop1871);
    _mm256_storeu_pd(&y[((i0 + 4) + 679)], __mv_vop1871);
    // y[1 * i0 + 679] += A[i0 + 1312] * x[1 * i0 + 678];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 679] += A[i0 + 1312] * x[1 * i0 + 678];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop990 = _mm256_loadu_pd(&A[((i0 + 0) + 1320)]);
    __mv_vop991 = _mm256_loadu_pd(&x[((i0 + 0) + 687)]);
    __mv_vop993 = _mm256_loadu_pd(&A[((i0 + 4) + 1320)]);
    __mv_vop994 = _mm256_loadu_pd(&x[((i0 + 4) + 687)]);
    __mv_vop1872 = _mm256_loadu_pd(&y[((i0 + 0) + 686)]);
    __mv_vop1872 = _mm256_fmadd_pd(__mv_vop990, __mv_vop991, __mv_vop1872);
    _mm256_storeu_pd(&y[((i0 + 0) + 686)], __mv_vop1872);
    __mv_vop1873 = _mm256_loadu_pd(&y[((i0 + 4) + 686)]);
    __mv_vop1873 = _mm256_fmadd_pd(__mv_vop993, __mv_vop994, __mv_vop1873);
    _mm256_storeu_pd(&y[((i0 + 4) + 686)], __mv_vop1873);
    // y[1 * i0 + 686] += A[i0 + 1320] * x[1 * i0 + 687];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 686] += A[i0 + 1320] * x[1 * i0 + 687];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop996 = _mm256_loadu_pd(&A[((i0 + 0) + 1328)]);
    __mv_vop997 = _mm256_loadu_pd(&x[((i0 + 0) + 686)]);
    __mv_vop999 = _mm256_loadu_pd(&A[((i0 + 4) + 1328)]);
    __mv_vop1000 = _mm256_loadu_pd(&x[((i0 + 4) + 686)]);
    __mv_vop1874 = _mm256_loadu_pd(&y[((i0 + 0) + 687)]);
    __mv_vop1874 = _mm256_fmadd_pd(__mv_vop996, __mv_vop997, __mv_vop1874);
    _mm256_storeu_pd(&y[((i0 + 0) + 687)], __mv_vop1874);
    __mv_vop1875 = _mm256_loadu_pd(&y[((i0 + 4) + 687)]);
    __mv_vop1875 = _mm256_fmadd_pd(__mv_vop999, __mv_vop1000, __mv_vop1875);
    _mm256_storeu_pd(&y[((i0 + 4) + 687)], __mv_vop1875);
    // y[1 * i0 + 687] += A[i0 + 1328] * x[1 * i0 + 686];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 687] += A[i0 + 1328] * x[1 * i0 + 686];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1002 = _mm256_loadu_pd(&A[((i0 + 0) + 1336)]);
    __mv_vop1003 = _mm256_loadu_pd(&x[((i0 + 0) + 695)]);
    __mv_vop1005 = _mm256_loadu_pd(&A[((i0 + 4) + 1336)]);
    __mv_vop1006 = _mm256_loadu_pd(&x[((i0 + 4) + 695)]);
    __mv_vop1876 = _mm256_loadu_pd(&y[((i0 + 0) + 694)]);
    __mv_vop1876 = _mm256_fmadd_pd(__mv_vop1002, __mv_vop1003, __mv_vop1876);
    _mm256_storeu_pd(&y[((i0 + 0) + 694)], __mv_vop1876);
    __mv_vop1877 = _mm256_loadu_pd(&y[((i0 + 4) + 694)]);
    __mv_vop1877 = _mm256_fmadd_pd(__mv_vop1005, __mv_vop1006, __mv_vop1877);
    _mm256_storeu_pd(&y[((i0 + 4) + 694)], __mv_vop1877);
    // y[1 * i0 + 694] += A[i0 + 1336] * x[1 * i0 + 695];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 694] += A[i0 + 1336] * x[1 * i0 + 695];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1008 = _mm256_loadu_pd(&A[((i0 + 0) + 1344)]);
    __mv_vop1009 = _mm256_loadu_pd(&x[((i0 + 0) + 694)]);
    __mv_vop1011 = _mm256_loadu_pd(&A[((i0 + 4) + 1344)]);
    __mv_vop1012 = _mm256_loadu_pd(&x[((i0 + 4) + 694)]);
    __mv_vop1878 = _mm256_loadu_pd(&y[((i0 + 0) + 695)]);
    __mv_vop1878 = _mm256_fmadd_pd(__mv_vop1008, __mv_vop1009, __mv_vop1878);
    _mm256_storeu_pd(&y[((i0 + 0) + 695)], __mv_vop1878);
    __mv_vop1879 = _mm256_loadu_pd(&y[((i0 + 4) + 695)]);
    __mv_vop1879 = _mm256_fmadd_pd(__mv_vop1011, __mv_vop1012, __mv_vop1879);
    _mm256_storeu_pd(&y[((i0 + 4) + 695)], __mv_vop1879);
    // y[1 * i0 + 695] += A[i0 + 1344] * x[1 * i0 + 694];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 695] += A[i0 + 1344] * x[1 * i0 + 694];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1014 = _mm256_loadu_pd(&A[((i0 + 0) + 1352)]);
    __mv_vop1015 = _mm256_loadu_pd(&x[((i0 + 0) + 703)]);
    __mv_vop1017 = _mm256_loadu_pd(&A[((i0 + 4) + 1352)]);
    __mv_vop1018 = _mm256_loadu_pd(&x[((i0 + 4) + 703)]);
    __mv_vop1880 = _mm256_loadu_pd(&y[((i0 + 0) + 702)]);
    __mv_vop1880 = _mm256_fmadd_pd(__mv_vop1014, __mv_vop1015, __mv_vop1880);
    _mm256_storeu_pd(&y[((i0 + 0) + 702)], __mv_vop1880);
    __mv_vop1881 = _mm256_loadu_pd(&y[((i0 + 4) + 702)]);
    __mv_vop1881 = _mm256_fmadd_pd(__mv_vop1017, __mv_vop1018, __mv_vop1881);
    _mm256_storeu_pd(&y[((i0 + 4) + 702)], __mv_vop1881);
    // y[1 * i0 + 702] += A[i0 + 1352] * x[1 * i0 + 703];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 702] += A[i0 + 1352] * x[1 * i0 + 703];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1020 = _mm256_loadu_pd(&A[((i0 + 0) + 1360)]);
    __mv_vop1021 = _mm256_loadu_pd(&x[((i0 + 0) + 702)]);
    __mv_vop1023 = _mm256_loadu_pd(&A[((i0 + 4) + 1360)]);
    __mv_vop1024 = _mm256_loadu_pd(&x[((i0 + 4) + 702)]);
    __mv_vop1882 = _mm256_loadu_pd(&y[((i0 + 0) + 703)]);
    __mv_vop1882 = _mm256_fmadd_pd(__mv_vop1020, __mv_vop1021, __mv_vop1882);
    _mm256_storeu_pd(&y[((i0 + 0) + 703)], __mv_vop1882);
    __mv_vop1883 = _mm256_loadu_pd(&y[((i0 + 4) + 703)]);
    __mv_vop1883 = _mm256_fmadd_pd(__mv_vop1023, __mv_vop1024, __mv_vop1883);
    _mm256_storeu_pd(&y[((i0 + 4) + 703)], __mv_vop1883);
    // y[1 * i0 + 703] += A[i0 + 1360] * x[1 * i0 + 702];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 703] += A[i0 + 1360] * x[1 * i0 + 702];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1026 = _mm256_loadu_pd(&A[((i0 + 0) + 1368)]);
    __mv_vop1027 = _mm256_loadu_pd(&x[((i0 + 0) + 711)]);
    __mv_vop1029 = _mm256_loadu_pd(&A[((i0 + 4) + 1368)]);
    __mv_vop1030 = _mm256_loadu_pd(&x[((i0 + 4) + 711)]);
    __mv_vop1884 = _mm256_loadu_pd(&y[((i0 + 0) + 710)]);
    __mv_vop1884 = _mm256_fmadd_pd(__mv_vop1026, __mv_vop1027, __mv_vop1884);
    _mm256_storeu_pd(&y[((i0 + 0) + 710)], __mv_vop1884);
    __mv_vop1885 = _mm256_loadu_pd(&y[((i0 + 4) + 710)]);
    __mv_vop1885 = _mm256_fmadd_pd(__mv_vop1029, __mv_vop1030, __mv_vop1885);
    _mm256_storeu_pd(&y[((i0 + 4) + 710)], __mv_vop1885);
    // y[1 * i0 + 710] += A[i0 + 1368] * x[1 * i0 + 711];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 710] += A[i0 + 1368] * x[1 * i0 + 711];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1032 = _mm256_loadu_pd(&A[((i0 + 0) + 1376)]);
    __mv_vop1033 = _mm256_loadu_pd(&x[((i0 + 0) + 710)]);
    __mv_vop1035 = _mm256_loadu_pd(&A[((i0 + 4) + 1376)]);
    __mv_vop1036 = _mm256_loadu_pd(&x[((i0 + 4) + 710)]);
    __mv_vop1886 = _mm256_loadu_pd(&y[((i0 + 0) + 711)]);
    __mv_vop1886 = _mm256_fmadd_pd(__mv_vop1032, __mv_vop1033, __mv_vop1886);
    _mm256_storeu_pd(&y[((i0 + 0) + 711)], __mv_vop1886);
    __mv_vop1887 = _mm256_loadu_pd(&y[((i0 + 4) + 711)]);
    __mv_vop1887 = _mm256_fmadd_pd(__mv_vop1035, __mv_vop1036, __mv_vop1887);
    _mm256_storeu_pd(&y[((i0 + 4) + 711)], __mv_vop1887);
    // y[1 * i0 + 711] += A[i0 + 1376] * x[1 * i0 + 710];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 711] += A[i0 + 1376] * x[1 * i0 + 710];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1038 = _mm256_loadu_pd(&A[((i0 + 0) + 1384)]);
    __mv_vop1039 = _mm256_loadu_pd(&x[((i0 + 0) + 719)]);
    __mv_vop1041 = _mm256_loadu_pd(&A[((i0 + 4) + 1384)]);
    __mv_vop1042 = _mm256_loadu_pd(&x[((i0 + 4) + 719)]);
    __mv_vop1888 = _mm256_loadu_pd(&y[((i0 + 0) + 718)]);
    __mv_vop1888 = _mm256_fmadd_pd(__mv_vop1038, __mv_vop1039, __mv_vop1888);
    _mm256_storeu_pd(&y[((i0 + 0) + 718)], __mv_vop1888);
    __mv_vop1889 = _mm256_loadu_pd(&y[((i0 + 4) + 718)]);
    __mv_vop1889 = _mm256_fmadd_pd(__mv_vop1041, __mv_vop1042, __mv_vop1889);
    _mm256_storeu_pd(&y[((i0 + 4) + 718)], __mv_vop1889);
    // y[1 * i0 + 718] += A[i0 + 1384] * x[1 * i0 + 719];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 718] += A[i0 + 1384] * x[1 * i0 + 719];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1044 = _mm256_loadu_pd(&A[((i0 + 0) + 1392)]);
    __mv_vop1045 = _mm256_loadu_pd(&x[((i0 + 0) + 718)]);
    __mv_vop1047 = _mm256_loadu_pd(&A[((i0 + 4) + 1392)]);
    __mv_vop1048 = _mm256_loadu_pd(&x[((i0 + 4) + 718)]);
    __mv_vop1890 = _mm256_loadu_pd(&y[((i0 + 0) + 719)]);
    __mv_vop1890 = _mm256_fmadd_pd(__mv_vop1044, __mv_vop1045, __mv_vop1890);
    _mm256_storeu_pd(&y[((i0 + 0) + 719)], __mv_vop1890);
    __mv_vop1891 = _mm256_loadu_pd(&y[((i0 + 4) + 719)]);
    __mv_vop1891 = _mm256_fmadd_pd(__mv_vop1047, __mv_vop1048, __mv_vop1891);
    _mm256_storeu_pd(&y[((i0 + 4) + 719)], __mv_vop1891);
    // y[1 * i0 + 719] += A[i0 + 1392] * x[1 * i0 + 718];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 719] += A[i0 + 1392] * x[1 * i0 + 718];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1050 = _mm256_loadu_pd(&A[((i0 + 0) + 1400)]);
    __mv_vop1051 = _mm256_loadu_pd(&x[((i0 + 0) + 727)]);
    __mv_vop1053 = _mm256_loadu_pd(&A[((i0 + 4) + 1400)]);
    __mv_vop1054 = _mm256_loadu_pd(&x[((i0 + 4) + 727)]);
    __mv_vop1892 = _mm256_loadu_pd(&y[((i0 + 0) + 726)]);
    __mv_vop1892 = _mm256_fmadd_pd(__mv_vop1050, __mv_vop1051, __mv_vop1892);
    _mm256_storeu_pd(&y[((i0 + 0) + 726)], __mv_vop1892);
    __mv_vop1893 = _mm256_loadu_pd(&y[((i0 + 4) + 726)]);
    __mv_vop1893 = _mm256_fmadd_pd(__mv_vop1053, __mv_vop1054, __mv_vop1893);
    _mm256_storeu_pd(&y[((i0 + 4) + 726)], __mv_vop1893);
    // y[1 * i0 + 726] += A[i0 + 1400] * x[1 * i0 + 727];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 726] += A[i0 + 1400] * x[1 * i0 + 727];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1056 = _mm256_loadu_pd(&A[((i0 + 0) + 1408)]);
    __mv_vop1057 = _mm256_loadu_pd(&x[((i0 + 0) + 726)]);
    __mv_vop1059 = _mm256_loadu_pd(&A[((i0 + 4) + 1408)]);
    __mv_vop1060 = _mm256_loadu_pd(&x[((i0 + 4) + 726)]);
    __mv_vop1894 = _mm256_loadu_pd(&y[((i0 + 0) + 727)]);
    __mv_vop1894 = _mm256_fmadd_pd(__mv_vop1056, __mv_vop1057, __mv_vop1894);
    _mm256_storeu_pd(&y[((i0 + 0) + 727)], __mv_vop1894);
    __mv_vop1895 = _mm256_loadu_pd(&y[((i0 + 4) + 727)]);
    __mv_vop1895 = _mm256_fmadd_pd(__mv_vop1059, __mv_vop1060, __mv_vop1895);
    _mm256_storeu_pd(&y[((i0 + 4) + 727)], __mv_vop1895);
    // y[1 * i0 + 727] += A[i0 + 1408] * x[1 * i0 + 726];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 727] += A[i0 + 1408] * x[1 * i0 + 726];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1062 = _mm256_loadu_pd(&A[((i0 + 0) + 1416)]);
    __mv_vop1063 = _mm256_loadu_pd(&x[((i0 + 0) + 735)]);
    __mv_vop1065 = _mm256_loadu_pd(&A[((i0 + 4) + 1416)]);
    __mv_vop1066 = _mm256_loadu_pd(&x[((i0 + 4) + 735)]);
    __mv_vop1896 = _mm256_loadu_pd(&y[((i0 + 0) + 734)]);
    __mv_vop1896 = _mm256_fmadd_pd(__mv_vop1062, __mv_vop1063, __mv_vop1896);
    _mm256_storeu_pd(&y[((i0 + 0) + 734)], __mv_vop1896);
    __mv_vop1897 = _mm256_loadu_pd(&y[((i0 + 4) + 734)]);
    __mv_vop1897 = _mm256_fmadd_pd(__mv_vop1065, __mv_vop1066, __mv_vop1897);
    _mm256_storeu_pd(&y[((i0 + 4) + 734)], __mv_vop1897);
    // y[1 * i0 + 734] += A[i0 + 1416] * x[1 * i0 + 735];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 734] += A[i0 + 1416] * x[1 * i0 + 735];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1068 = _mm256_loadu_pd(&A[((i0 + 0) + 1424)]);
    __mv_vop1069 = _mm256_loadu_pd(&x[((i0 + 0) + 734)]);
    __mv_vop1071 = _mm256_loadu_pd(&A[((i0 + 4) + 1424)]);
    __mv_vop1072 = _mm256_loadu_pd(&x[((i0 + 4) + 734)]);
    __mv_vop1898 = _mm256_loadu_pd(&y[((i0 + 0) + 735)]);
    __mv_vop1898 = _mm256_fmadd_pd(__mv_vop1068, __mv_vop1069, __mv_vop1898);
    _mm256_storeu_pd(&y[((i0 + 0) + 735)], __mv_vop1898);
    __mv_vop1899 = _mm256_loadu_pd(&y[((i0 + 4) + 735)]);
    __mv_vop1899 = _mm256_fmadd_pd(__mv_vop1071, __mv_vop1072, __mv_vop1899);
    _mm256_storeu_pd(&y[((i0 + 4) + 735)], __mv_vop1899);
    // y[1 * i0 + 735] += A[i0 + 1424] * x[1 * i0 + 734];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 735] += A[i0 + 1424] * x[1 * i0 + 734];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1074 = _mm256_loadu_pd(&A[((i0 + 0) + 1432)]);
    __mv_vop1075 = _mm256_loadu_pd(&x[((i0 + 0) + 743)]);
    __mv_vop1077 = _mm256_loadu_pd(&A[((i0 + 4) + 1432)]);
    __mv_vop1078 = _mm256_loadu_pd(&x[((i0 + 4) + 743)]);
    __mv_vop1900 = _mm256_loadu_pd(&y[((i0 + 0) + 742)]);
    __mv_vop1900 = _mm256_fmadd_pd(__mv_vop1074, __mv_vop1075, __mv_vop1900);
    _mm256_storeu_pd(&y[((i0 + 0) + 742)], __mv_vop1900);
    __mv_vop1901 = _mm256_loadu_pd(&y[((i0 + 4) + 742)]);
    __mv_vop1901 = _mm256_fmadd_pd(__mv_vop1077, __mv_vop1078, __mv_vop1901);
    _mm256_storeu_pd(&y[((i0 + 4) + 742)], __mv_vop1901);
    // y[1 * i0 + 742] += A[i0 + 1432] * x[1 * i0 + 743];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 742] += A[i0 + 1432] * x[1 * i0 + 743];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1080 = _mm256_loadu_pd(&A[((i0 + 0) + 1440)]);
    __mv_vop1081 = _mm256_loadu_pd(&x[((i0 + 0) + 742)]);
    __mv_vop1083 = _mm256_loadu_pd(&A[((i0 + 4) + 1440)]);
    __mv_vop1084 = _mm256_loadu_pd(&x[((i0 + 4) + 742)]);
    __mv_vop1902 = _mm256_loadu_pd(&y[((i0 + 0) + 743)]);
    __mv_vop1902 = _mm256_fmadd_pd(__mv_vop1080, __mv_vop1081, __mv_vop1902);
    _mm256_storeu_pd(&y[((i0 + 0) + 743)], __mv_vop1902);
    __mv_vop1903 = _mm256_loadu_pd(&y[((i0 + 4) + 743)]);
    __mv_vop1903 = _mm256_fmadd_pd(__mv_vop1083, __mv_vop1084, __mv_vop1903);
    _mm256_storeu_pd(&y[((i0 + 4) + 743)], __mv_vop1903);
    // y[1 * i0 + 743] += A[i0 + 1440] * x[1 * i0 + 742];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 743] += A[i0 + 1440] * x[1 * i0 + 742];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1086 = _mm256_loadu_pd(&A[((i0 + 0) + 1448)]);
    __mv_vop1087 = _mm256_loadu_pd(&x[((i0 + 0) + 751)]);
    __mv_vop1089 = _mm256_loadu_pd(&A[((i0 + 4) + 1448)]);
    __mv_vop1090 = _mm256_loadu_pd(&x[((i0 + 4) + 751)]);
    __mv_vop1904 = _mm256_loadu_pd(&y[((i0 + 0) + 750)]);
    __mv_vop1904 = _mm256_fmadd_pd(__mv_vop1086, __mv_vop1087, __mv_vop1904);
    _mm256_storeu_pd(&y[((i0 + 0) + 750)], __mv_vop1904);
    __mv_vop1905 = _mm256_loadu_pd(&y[((i0 + 4) + 750)]);
    __mv_vop1905 = _mm256_fmadd_pd(__mv_vop1089, __mv_vop1090, __mv_vop1905);
    _mm256_storeu_pd(&y[((i0 + 4) + 750)], __mv_vop1905);
    // y[1 * i0 + 750] += A[i0 + 1448] * x[1 * i0 + 751];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 750] += A[i0 + 1448] * x[1 * i0 + 751];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1092 = _mm256_loadu_pd(&A[((i0 + 0) + 1456)]);
    __mv_vop1093 = _mm256_loadu_pd(&x[((i0 + 0) + 750)]);
    __mv_vop1095 = _mm256_loadu_pd(&A[((i0 + 4) + 1456)]);
    __mv_vop1096 = _mm256_loadu_pd(&x[((i0 + 4) + 750)]);
    __mv_vop1906 = _mm256_loadu_pd(&y[((i0 + 0) + 751)]);
    __mv_vop1906 = _mm256_fmadd_pd(__mv_vop1092, __mv_vop1093, __mv_vop1906);
    _mm256_storeu_pd(&y[((i0 + 0) + 751)], __mv_vop1906);
    __mv_vop1907 = _mm256_loadu_pd(&y[((i0 + 4) + 751)]);
    __mv_vop1907 = _mm256_fmadd_pd(__mv_vop1095, __mv_vop1096, __mv_vop1907);
    _mm256_storeu_pd(&y[((i0 + 4) + 751)], __mv_vop1907);
    // y[1 * i0 + 751] += A[i0 + 1456] * x[1 * i0 + 750];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 751] += A[i0 + 1456] * x[1 * i0 + 750];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1098 = _mm256_loadu_pd(&A[((i0 + 0) + 1464)]);
    __mv_vop1099 = _mm256_loadu_pd(&x[((i0 + 0) + 759)]);
    __mv_vop1101 = _mm256_loadu_pd(&A[((i0 + 4) + 1464)]);
    __mv_vop1102 = _mm256_loadu_pd(&x[((i0 + 4) + 759)]);
    __mv_vop1908 = _mm256_loadu_pd(&y[((i0 + 0) + 758)]);
    __mv_vop1908 = _mm256_fmadd_pd(__mv_vop1098, __mv_vop1099, __mv_vop1908);
    _mm256_storeu_pd(&y[((i0 + 0) + 758)], __mv_vop1908);
    __mv_vop1909 = _mm256_loadu_pd(&y[((i0 + 4) + 758)]);
    __mv_vop1909 = _mm256_fmadd_pd(__mv_vop1101, __mv_vop1102, __mv_vop1909);
    _mm256_storeu_pd(&y[((i0 + 4) + 758)], __mv_vop1909);
    // y[1 * i0 + 758] += A[i0 + 1464] * x[1 * i0 + 759];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 758] += A[i0 + 1464] * x[1 * i0 + 759];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1104 = _mm256_loadu_pd(&A[((i0 + 0) + 1472)]);
    __mv_vop1105 = _mm256_loadu_pd(&x[((i0 + 0) + 758)]);
    __mv_vop1107 = _mm256_loadu_pd(&A[((i0 + 4) + 1472)]);
    __mv_vop1108 = _mm256_loadu_pd(&x[((i0 + 4) + 758)]);
    __mv_vop1910 = _mm256_loadu_pd(&y[((i0 + 0) + 759)]);
    __mv_vop1910 = _mm256_fmadd_pd(__mv_vop1104, __mv_vop1105, __mv_vop1910);
    _mm256_storeu_pd(&y[((i0 + 0) + 759)], __mv_vop1910);
    __mv_vop1911 = _mm256_loadu_pd(&y[((i0 + 4) + 759)]);
    __mv_vop1911 = _mm256_fmadd_pd(__mv_vop1107, __mv_vop1108, __mv_vop1911);
    _mm256_storeu_pd(&y[((i0 + 4) + 759)], __mv_vop1911);
    // y[1 * i0 + 759] += A[i0 + 1472] * x[1 * i0 + 758];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 759] += A[i0 + 1472] * x[1 * i0 + 758];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1110 = _mm256_loadu_pd(&A[((i0 + 0) + 1480)]);
    __mv_vop1111 = _mm256_loadu_pd(&x[((i0 + 0) + 767)]);
    __mv_vop1113 = _mm256_loadu_pd(&A[((i0 + 4) + 1480)]);
    __mv_vop1114 = _mm256_loadu_pd(&x[((i0 + 4) + 767)]);
    __mv_vop1912 = _mm256_loadu_pd(&y[((i0 + 0) + 766)]);
    __mv_vop1912 = _mm256_fmadd_pd(__mv_vop1110, __mv_vop1111, __mv_vop1912);
    _mm256_storeu_pd(&y[((i0 + 0) + 766)], __mv_vop1912);
    __mv_vop1913 = _mm256_loadu_pd(&y[((i0 + 4) + 766)]);
    __mv_vop1913 = _mm256_fmadd_pd(__mv_vop1113, __mv_vop1114, __mv_vop1913);
    _mm256_storeu_pd(&y[((i0 + 4) + 766)], __mv_vop1913);
    // y[1 * i0 + 766] += A[i0 + 1480] * x[1 * i0 + 767];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 766] += A[i0 + 1480] * x[1 * i0 + 767];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1116 = _mm256_loadu_pd(&A[((i0 + 0) + 1488)]);
    __mv_vop1117 = _mm256_loadu_pd(&x[((i0 + 0) + 766)]);
    __mv_vop1119 = _mm256_loadu_pd(&A[((i0 + 4) + 1488)]);
    __mv_vop1120 = _mm256_loadu_pd(&x[((i0 + 4) + 766)]);
    __mv_vop1914 = _mm256_loadu_pd(&y[((i0 + 0) + 767)]);
    __mv_vop1914 = _mm256_fmadd_pd(__mv_vop1116, __mv_vop1117, __mv_vop1914);
    _mm256_storeu_pd(&y[((i0 + 0) + 767)], __mv_vop1914);
    __mv_vop1915 = _mm256_loadu_pd(&y[((i0 + 4) + 767)]);
    __mv_vop1915 = _mm256_fmadd_pd(__mv_vop1119, __mv_vop1120, __mv_vop1915);
    _mm256_storeu_pd(&y[((i0 + 4) + 767)], __mv_vop1915);
    // y[1 * i0 + 767] += A[i0 + 1488] * x[1 * i0 + 766];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 767] += A[i0 + 1488] * x[1 * i0 + 766];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1122 = _mm256_loadu_pd(&A[((i0 + 0) + 1496)]);
    __mv_vop1123 = _mm256_loadu_pd(&x[((i0 + 0) + 775)]);
    __mv_vop1125 = _mm256_loadu_pd(&A[((i0 + 4) + 1496)]);
    __mv_vop1126 = _mm256_loadu_pd(&x[((i0 + 4) + 775)]);
    __mv_vop1916 = _mm256_loadu_pd(&y[((i0 + 0) + 774)]);
    __mv_vop1916 = _mm256_fmadd_pd(__mv_vop1122, __mv_vop1123, __mv_vop1916);
    _mm256_storeu_pd(&y[((i0 + 0) + 774)], __mv_vop1916);
    __mv_vop1917 = _mm256_loadu_pd(&y[((i0 + 4) + 774)]);
    __mv_vop1917 = _mm256_fmadd_pd(__mv_vop1125, __mv_vop1126, __mv_vop1917);
    _mm256_storeu_pd(&y[((i0 + 4) + 774)], __mv_vop1917);
    // y[1 * i0 + 774] += A[i0 + 1496] * x[1 * i0 + 775];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 774] += A[i0 + 1496] * x[1 * i0 + 775];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1128 = _mm256_loadu_pd(&A[((i0 + 0) + 1504)]);
    __mv_vop1129 = _mm256_loadu_pd(&x[((i0 + 0) + 774)]);
    __mv_vop1131 = _mm256_loadu_pd(&A[((i0 + 4) + 1504)]);
    __mv_vop1132 = _mm256_loadu_pd(&x[((i0 + 4) + 774)]);
    __mv_vop1918 = _mm256_loadu_pd(&y[((i0 + 0) + 775)]);
    __mv_vop1918 = _mm256_fmadd_pd(__mv_vop1128, __mv_vop1129, __mv_vop1918);
    _mm256_storeu_pd(&y[((i0 + 0) + 775)], __mv_vop1918);
    __mv_vop1919 = _mm256_loadu_pd(&y[((i0 + 4) + 775)]);
    __mv_vop1919 = _mm256_fmadd_pd(__mv_vop1131, __mv_vop1132, __mv_vop1919);
    _mm256_storeu_pd(&y[((i0 + 4) + 775)], __mv_vop1919);
    // y[1 * i0 + 775] += A[i0 + 1504] * x[1 * i0 + 774];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 775] += A[i0 + 1504] * x[1 * i0 + 774];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1134 = _mm256_loadu_pd(&A[((i0 + 0) + 1512)]);
    __mv_vop1135 = _mm256_loadu_pd(&x[((i0 + 0) + 783)]);
    __mv_vop1137 = _mm256_loadu_pd(&A[((i0 + 4) + 1512)]);
    __mv_vop1138 = _mm256_loadu_pd(&x[((i0 + 4) + 783)]);
    __mv_vop1920 = _mm256_loadu_pd(&y[((i0 + 0) + 782)]);
    __mv_vop1920 = _mm256_fmadd_pd(__mv_vop1134, __mv_vop1135, __mv_vop1920);
    _mm256_storeu_pd(&y[((i0 + 0) + 782)], __mv_vop1920);
    __mv_vop1921 = _mm256_loadu_pd(&y[((i0 + 4) + 782)]);
    __mv_vop1921 = _mm256_fmadd_pd(__mv_vop1137, __mv_vop1138, __mv_vop1921);
    _mm256_storeu_pd(&y[((i0 + 4) + 782)], __mv_vop1921);
    // y[1 * i0 + 782] += A[i0 + 1512] * x[1 * i0 + 783];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 782] += A[i0 + 1512] * x[1 * i0 + 783];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1140 = _mm256_loadu_pd(&A[((i0 + 0) + 1520)]);
    __mv_vop1141 = _mm256_loadu_pd(&x[((i0 + 0) + 782)]);
    __mv_vop1143 = _mm256_loadu_pd(&A[((i0 + 4) + 1520)]);
    __mv_vop1144 = _mm256_loadu_pd(&x[((i0 + 4) + 782)]);
    __mv_vop1922 = _mm256_loadu_pd(&y[((i0 + 0) + 783)]);
    __mv_vop1922 = _mm256_fmadd_pd(__mv_vop1140, __mv_vop1141, __mv_vop1922);
    _mm256_storeu_pd(&y[((i0 + 0) + 783)], __mv_vop1922);
    __mv_vop1923 = _mm256_loadu_pd(&y[((i0 + 4) + 783)]);
    __mv_vop1923 = _mm256_fmadd_pd(__mv_vop1143, __mv_vop1144, __mv_vop1923);
    _mm256_storeu_pd(&y[((i0 + 4) + 783)], __mv_vop1923);
    // y[1 * i0 + 783] += A[i0 + 1520] * x[1 * i0 + 782];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 783] += A[i0 + 1520] * x[1 * i0 + 782];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1146 = _mm256_loadu_pd(&A[((i0 + 0) + 1528)]);
    __mv_vop1147 = _mm256_loadu_pd(&x[((i0 + 0) + 791)]);
    __mv_vop1149 = _mm256_loadu_pd(&A[((i0 + 4) + 1528)]);
    __mv_vop1150 = _mm256_loadu_pd(&x[((i0 + 4) + 791)]);
    __mv_vop1924 = _mm256_loadu_pd(&y[((i0 + 0) + 790)]);
    __mv_vop1924 = _mm256_fmadd_pd(__mv_vop1146, __mv_vop1147, __mv_vop1924);
    _mm256_storeu_pd(&y[((i0 + 0) + 790)], __mv_vop1924);
    __mv_vop1925 = _mm256_loadu_pd(&y[((i0 + 4) + 790)]);
    __mv_vop1925 = _mm256_fmadd_pd(__mv_vop1149, __mv_vop1150, __mv_vop1925);
    _mm256_storeu_pd(&y[((i0 + 4) + 790)], __mv_vop1925);
    // y[1 * i0 + 790] += A[i0 + 1528] * x[1 * i0 + 791];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 790] += A[i0 + 1528] * x[1 * i0 + 791];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1152 = _mm256_loadu_pd(&A[((i0 + 0) + 1536)]);
    __mv_vop1153 = _mm256_loadu_pd(&x[((i0 + 0) + 790)]);
    __mv_vop1155 = _mm256_loadu_pd(&A[((i0 + 4) + 1536)]);
    __mv_vop1156 = _mm256_loadu_pd(&x[((i0 + 4) + 790)]);
    __mv_vop1926 = _mm256_loadu_pd(&y[((i0 + 0) + 791)]);
    __mv_vop1926 = _mm256_fmadd_pd(__mv_vop1152, __mv_vop1153, __mv_vop1926);
    _mm256_storeu_pd(&y[((i0 + 0) + 791)], __mv_vop1926);
    __mv_vop1927 = _mm256_loadu_pd(&y[((i0 + 4) + 791)]);
    __mv_vop1927 = _mm256_fmadd_pd(__mv_vop1155, __mv_vop1156, __mv_vop1927);
    _mm256_storeu_pd(&y[((i0 + 4) + 791)], __mv_vop1927);
    // y[1 * i0 + 791] += A[i0 + 1536] * x[1 * i0 + 790];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 791] += A[i0 + 1536] * x[1 * i0 + 790];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1158 = _mm256_loadu_pd(&A[((i0 + 0) + 1544)]);
    __mv_vop1159 = _mm256_loadu_pd(&x[((i0 + 0) + 799)]);
    __mv_vop1161 = _mm256_loadu_pd(&A[((i0 + 4) + 1544)]);
    __mv_vop1162 = _mm256_loadu_pd(&x[((i0 + 4) + 799)]);
    __mv_vop1928 = _mm256_loadu_pd(&y[((i0 + 0) + 798)]);
    __mv_vop1928 = _mm256_fmadd_pd(__mv_vop1158, __mv_vop1159, __mv_vop1928);
    _mm256_storeu_pd(&y[((i0 + 0) + 798)], __mv_vop1928);
    __mv_vop1929 = _mm256_loadu_pd(&y[((i0 + 4) + 798)]);
    __mv_vop1929 = _mm256_fmadd_pd(__mv_vop1161, __mv_vop1162, __mv_vop1929);
    _mm256_storeu_pd(&y[((i0 + 4) + 798)], __mv_vop1929);
    // y[1 * i0 + 798] += A[i0 + 1544] * x[1 * i0 + 799];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 798] += A[i0 + 1544] * x[1 * i0 + 799];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1164 = _mm256_loadu_pd(&A[((i0 + 0) + 1552)]);
    __mv_vop1165 = _mm256_loadu_pd(&x[((i0 + 0) + 798)]);
    __mv_vop1167 = _mm256_loadu_pd(&A[((i0 + 4) + 1552)]);
    __mv_vop1168 = _mm256_loadu_pd(&x[((i0 + 4) + 798)]);
    __mv_vop1930 = _mm256_loadu_pd(&y[((i0 + 0) + 799)]);
    __mv_vop1930 = _mm256_fmadd_pd(__mv_vop1164, __mv_vop1165, __mv_vop1930);
    _mm256_storeu_pd(&y[((i0 + 0) + 799)], __mv_vop1930);
    __mv_vop1931 = _mm256_loadu_pd(&y[((i0 + 4) + 799)]);
    __mv_vop1931 = _mm256_fmadd_pd(__mv_vop1167, __mv_vop1168, __mv_vop1931);
    _mm256_storeu_pd(&y[((i0 + 4) + 799)], __mv_vop1931);
    // y[1 * i0 + 799] += A[i0 + 1552] * x[1 * i0 + 798];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 799] += A[i0 + 1552] * x[1 * i0 + 798];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1170 = _mm256_loadu_pd(&A[((i0 + 0) + 1560)]);
    __mv_vop1171 = _mm256_loadu_pd(&x[((i0 + 0) + 814)]);
    __mv_vop1173 = _mm256_loadu_pd(&A[((i0 + 4) + 1560)]);
    __mv_vop1174 = _mm256_loadu_pd(&x[((i0 + 4) + 814)]);
    __mv_vop1932 = _mm256_loadu_pd(&y[((i0 + 0) + 813)]);
    __mv_vop1932 = _mm256_fmadd_pd(__mv_vop1170, __mv_vop1171, __mv_vop1932);
    _mm256_storeu_pd(&y[((i0 + 0) + 813)], __mv_vop1932);
    __mv_vop1933 = _mm256_loadu_pd(&y[((i0 + 4) + 813)]);
    __mv_vop1933 = _mm256_fmadd_pd(__mv_vop1173, __mv_vop1174, __mv_vop1933);
    _mm256_storeu_pd(&y[((i0 + 4) + 813)], __mv_vop1933);
    // y[1 * i0 + 813] += A[i0 + 1560] * x[1 * i0 + 814];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 813] += A[i0 + 1560] * x[1 * i0 + 814];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1176 = _mm256_loadu_pd(&A[((i0 + 0) + 1568)]);
    __mv_vop1177 = _mm256_loadu_pd(&x[((i0 + 0) + 813)]);
    __mv_vop1179 = _mm256_loadu_pd(&A[((i0 + 4) + 1568)]);
    __mv_vop1180 = _mm256_loadu_pd(&x[((i0 + 4) + 813)]);
    __mv_vop1934 = _mm256_loadu_pd(&y[((i0 + 0) + 814)]);
    __mv_vop1934 = _mm256_fmadd_pd(__mv_vop1176, __mv_vop1177, __mv_vop1934);
    _mm256_storeu_pd(&y[((i0 + 0) + 814)], __mv_vop1934);
    __mv_vop1935 = _mm256_loadu_pd(&y[((i0 + 4) + 814)]);
    __mv_vop1935 = _mm256_fmadd_pd(__mv_vop1179, __mv_vop1180, __mv_vop1935);
    _mm256_storeu_pd(&y[((i0 + 4) + 814)], __mv_vop1935);
    // y[1 * i0 + 814] += A[i0 + 1568] * x[1 * i0 + 813];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 814] += A[i0 + 1568] * x[1 * i0 + 813];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1182 = _mm256_loadu_pd(&A[((i0 + 0) + 1576)]);
    __mv_vop1183 = _mm256_loadu_pd(&x[((i0 + 0) + 822)]);
    __mv_vop1185 = _mm256_loadu_pd(&A[((i0 + 4) + 1576)]);
    __mv_vop1186 = _mm256_loadu_pd(&x[((i0 + 4) + 822)]);
    __mv_vop1936 = _mm256_loadu_pd(&y[((i0 + 0) + 821)]);
    __mv_vop1936 = _mm256_fmadd_pd(__mv_vop1182, __mv_vop1183, __mv_vop1936);
    _mm256_storeu_pd(&y[((i0 + 0) + 821)], __mv_vop1936);
    __mv_vop1937 = _mm256_loadu_pd(&y[((i0 + 4) + 821)]);
    __mv_vop1937 = _mm256_fmadd_pd(__mv_vop1185, __mv_vop1186, __mv_vop1937);
    _mm256_storeu_pd(&y[((i0 + 4) + 821)], __mv_vop1937);
    // y[1 * i0 + 821] += A[i0 + 1576] * x[1 * i0 + 822];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 821] += A[i0 + 1576] * x[1 * i0 + 822];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1188 = _mm256_loadu_pd(&A[((i0 + 0) + 1584)]);
    __mv_vop1189 = _mm256_loadu_pd(&x[((i0 + 0) + 821)]);
    __mv_vop1191 = _mm256_loadu_pd(&A[((i0 + 4) + 1584)]);
    __mv_vop1192 = _mm256_loadu_pd(&x[((i0 + 4) + 821)]);
    __mv_vop1938 = _mm256_loadu_pd(&y[((i0 + 0) + 822)]);
    __mv_vop1938 = _mm256_fmadd_pd(__mv_vop1188, __mv_vop1189, __mv_vop1938);
    _mm256_storeu_pd(&y[((i0 + 0) + 822)], __mv_vop1938);
    __mv_vop1939 = _mm256_loadu_pd(&y[((i0 + 4) + 822)]);
    __mv_vop1939 = _mm256_fmadd_pd(__mv_vop1191, __mv_vop1192, __mv_vop1939);
    _mm256_storeu_pd(&y[((i0 + 4) + 822)], __mv_vop1939);
    // y[1 * i0 + 822] += A[i0 + 1584] * x[1 * i0 + 821];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 822] += A[i0 + 1584] * x[1 * i0 + 821];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1194 = _mm256_loadu_pd(&A[((i0 + 0) + 1592)]);
    __mv_vop1195 = _mm256_loadu_pd(&x[((i0 + 0) + 830)]);
    __mv_vop1197 = _mm256_loadu_pd(&A[((i0 + 4) + 1592)]);
    __mv_vop1198 = _mm256_loadu_pd(&x[((i0 + 4) + 830)]);
    __mv_vop1940 = _mm256_loadu_pd(&y[((i0 + 0) + 829)]);
    __mv_vop1940 = _mm256_fmadd_pd(__mv_vop1194, __mv_vop1195, __mv_vop1940);
    _mm256_storeu_pd(&y[((i0 + 0) + 829)], __mv_vop1940);
    __mv_vop1941 = _mm256_loadu_pd(&y[((i0 + 4) + 829)]);
    __mv_vop1941 = _mm256_fmadd_pd(__mv_vop1197, __mv_vop1198, __mv_vop1941);
    _mm256_storeu_pd(&y[((i0 + 4) + 829)], __mv_vop1941);
    // y[1 * i0 + 829] += A[i0 + 1592] * x[1 * i0 + 830];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 829] += A[i0 + 1592] * x[1 * i0 + 830];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1200 = _mm256_loadu_pd(&A[((i0 + 0) + 1600)]);
    __mv_vop1201 = _mm256_loadu_pd(&x[((i0 + 0) + 829)]);
    __mv_vop1203 = _mm256_loadu_pd(&A[((i0 + 4) + 1600)]);
    __mv_vop1204 = _mm256_loadu_pd(&x[((i0 + 4) + 829)]);
    __mv_vop1942 = _mm256_loadu_pd(&y[((i0 + 0) + 830)]);
    __mv_vop1942 = _mm256_fmadd_pd(__mv_vop1200, __mv_vop1201, __mv_vop1942);
    _mm256_storeu_pd(&y[((i0 + 0) + 830)], __mv_vop1942);
    __mv_vop1943 = _mm256_loadu_pd(&y[((i0 + 4) + 830)]);
    __mv_vop1943 = _mm256_fmadd_pd(__mv_vop1203, __mv_vop1204, __mv_vop1943);
    _mm256_storeu_pd(&y[((i0 + 4) + 830)], __mv_vop1943);
    // y[1 * i0 + 830] += A[i0 + 1600] * x[1 * i0 + 829];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 830] += A[i0 + 1600] * x[1 * i0 + 829];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1206 = _mm256_loadu_pd(&A[((i0 + 0) + 1608)]);
    __mv_vop1207 = _mm256_loadu_pd(&x[((i0 + 0) + 838)]);
    __mv_vop1209 = _mm256_loadu_pd(&A[((i0 + 4) + 1608)]);
    __mv_vop1210 = _mm256_loadu_pd(&x[((i0 + 4) + 838)]);
    __mv_vop1944 = _mm256_loadu_pd(&y[((i0 + 0) + 837)]);
    __mv_vop1944 = _mm256_fmadd_pd(__mv_vop1206, __mv_vop1207, __mv_vop1944);
    _mm256_storeu_pd(&y[((i0 + 0) + 837)], __mv_vop1944);
    __mv_vop1945 = _mm256_loadu_pd(&y[((i0 + 4) + 837)]);
    __mv_vop1945 = _mm256_fmadd_pd(__mv_vop1209, __mv_vop1210, __mv_vop1945);
    _mm256_storeu_pd(&y[((i0 + 4) + 837)], __mv_vop1945);
    // y[1 * i0 + 837] += A[i0 + 1608] * x[1 * i0 + 838];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 837] += A[i0 + 1608] * x[1 * i0 + 838];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1212 = _mm256_loadu_pd(&A[((i0 + 0) + 1616)]);
    __mv_vop1213 = _mm256_loadu_pd(&x[((i0 + 0) + 837)]);
    __mv_vop1215 = _mm256_loadu_pd(&A[((i0 + 4) + 1616)]);
    __mv_vop1216 = _mm256_loadu_pd(&x[((i0 + 4) + 837)]);
    __mv_vop1946 = _mm256_loadu_pd(&y[((i0 + 0) + 838)]);
    __mv_vop1946 = _mm256_fmadd_pd(__mv_vop1212, __mv_vop1213, __mv_vop1946);
    _mm256_storeu_pd(&y[((i0 + 0) + 838)], __mv_vop1946);
    __mv_vop1947 = _mm256_loadu_pd(&y[((i0 + 4) + 838)]);
    __mv_vop1947 = _mm256_fmadd_pd(__mv_vop1215, __mv_vop1216, __mv_vop1947);
    _mm256_storeu_pd(&y[((i0 + 4) + 838)], __mv_vop1947);
    // y[1 * i0 + 838] += A[i0 + 1616] * x[1 * i0 + 837];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 838] += A[i0 + 1616] * x[1 * i0 + 837];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1218 = _mm256_loadu_pd(&A[((i0 + 0) + 1624)]);
    __mv_vop1219 = _mm256_loadu_pd(&x[((i0 + 0) + 846)]);
    __mv_vop1221 = _mm256_loadu_pd(&A[((i0 + 4) + 1624)]);
    __mv_vop1222 = _mm256_loadu_pd(&x[((i0 + 4) + 846)]);
    __mv_vop1948 = _mm256_loadu_pd(&y[((i0 + 0) + 845)]);
    __mv_vop1948 = _mm256_fmadd_pd(__mv_vop1218, __mv_vop1219, __mv_vop1948);
    _mm256_storeu_pd(&y[((i0 + 0) + 845)], __mv_vop1948);
    __mv_vop1949 = _mm256_loadu_pd(&y[((i0 + 4) + 845)]);
    __mv_vop1949 = _mm256_fmadd_pd(__mv_vop1221, __mv_vop1222, __mv_vop1949);
    _mm256_storeu_pd(&y[((i0 + 4) + 845)], __mv_vop1949);
    // y[1 * i0 + 845] += A[i0 + 1624] * x[1 * i0 + 846];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 845] += A[i0 + 1624] * x[1 * i0 + 846];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1224 = _mm256_loadu_pd(&A[((i0 + 0) + 1632)]);
    __mv_vop1225 = _mm256_loadu_pd(&x[((i0 + 0) + 845)]);
    __mv_vop1227 = _mm256_loadu_pd(&A[((i0 + 4) + 1632)]);
    __mv_vop1228 = _mm256_loadu_pd(&x[((i0 + 4) + 845)]);
    __mv_vop1950 = _mm256_loadu_pd(&y[((i0 + 0) + 846)]);
    __mv_vop1950 = _mm256_fmadd_pd(__mv_vop1224, __mv_vop1225, __mv_vop1950);
    _mm256_storeu_pd(&y[((i0 + 0) + 846)], __mv_vop1950);
    __mv_vop1951 = _mm256_loadu_pd(&y[((i0 + 4) + 846)]);
    __mv_vop1951 = _mm256_fmadd_pd(__mv_vop1227, __mv_vop1228, __mv_vop1951);
    _mm256_storeu_pd(&y[((i0 + 4) + 846)], __mv_vop1951);
    // y[1 * i0 + 846] += A[i0 + 1632] * x[1 * i0 + 845];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 846] += A[i0 + 1632] * x[1 * i0 + 845];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1230 = _mm256_loadu_pd(&A[((i0 + 0) + 1640)]);
    __mv_vop1231 = _mm256_loadu_pd(&x[((i0 + 0) + 854)]);
    __mv_vop1233 = _mm256_loadu_pd(&A[((i0 + 4) + 1640)]);
    __mv_vop1234 = _mm256_loadu_pd(&x[((i0 + 4) + 854)]);
    __mv_vop1952 = _mm256_loadu_pd(&y[((i0 + 0) + 853)]);
    __mv_vop1952 = _mm256_fmadd_pd(__mv_vop1230, __mv_vop1231, __mv_vop1952);
    _mm256_storeu_pd(&y[((i0 + 0) + 853)], __mv_vop1952);
    __mv_vop1953 = _mm256_loadu_pd(&y[((i0 + 4) + 853)]);
    __mv_vop1953 = _mm256_fmadd_pd(__mv_vop1233, __mv_vop1234, __mv_vop1953);
    _mm256_storeu_pd(&y[((i0 + 4) + 853)], __mv_vop1953);
    // y[1 * i0 + 853] += A[i0 + 1640] * x[1 * i0 + 854];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 853] += A[i0 + 1640] * x[1 * i0 + 854];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1236 = _mm256_loadu_pd(&A[((i0 + 0) + 1648)]);
    __mv_vop1237 = _mm256_loadu_pd(&x[((i0 + 0) + 853)]);
    __mv_vop1239 = _mm256_loadu_pd(&A[((i0 + 4) + 1648)]);
    __mv_vop1240 = _mm256_loadu_pd(&x[((i0 + 4) + 853)]);
    __mv_vop1954 = _mm256_loadu_pd(&y[((i0 + 0) + 854)]);
    __mv_vop1954 = _mm256_fmadd_pd(__mv_vop1236, __mv_vop1237, __mv_vop1954);
    _mm256_storeu_pd(&y[((i0 + 0) + 854)], __mv_vop1954);
    __mv_vop1955 = _mm256_loadu_pd(&y[((i0 + 4) + 854)]);
    __mv_vop1955 = _mm256_fmadd_pd(__mv_vop1239, __mv_vop1240, __mv_vop1955);
    _mm256_storeu_pd(&y[((i0 + 4) + 854)], __mv_vop1955);
    // y[1 * i0 + 854] += A[i0 + 1648] * x[1 * i0 + 853];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 854] += A[i0 + 1648] * x[1 * i0 + 853];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1242 = _mm256_loadu_pd(&A[((i0 + 0) + 1656)]);
    __mv_vop1243 = _mm256_loadu_pd(&x[((i0 + 0) + 862)]);
    __mv_vop1245 = _mm256_loadu_pd(&A[((i0 + 4) + 1656)]);
    __mv_vop1246 = _mm256_loadu_pd(&x[((i0 + 4) + 862)]);
    __mv_vop1956 = _mm256_loadu_pd(&y[((i0 + 0) + 861)]);
    __mv_vop1956 = _mm256_fmadd_pd(__mv_vop1242, __mv_vop1243, __mv_vop1956);
    _mm256_storeu_pd(&y[((i0 + 0) + 861)], __mv_vop1956);
    __mv_vop1957 = _mm256_loadu_pd(&y[((i0 + 4) + 861)]);
    __mv_vop1957 = _mm256_fmadd_pd(__mv_vop1245, __mv_vop1246, __mv_vop1957);
    _mm256_storeu_pd(&y[((i0 + 4) + 861)], __mv_vop1957);
    // y[1 * i0 + 861] += A[i0 + 1656] * x[1 * i0 + 862];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 861] += A[i0 + 1656] * x[1 * i0 + 862];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1248 = _mm256_loadu_pd(&A[((i0 + 0) + 1664)]);
    __mv_vop1249 = _mm256_loadu_pd(&x[((i0 + 0) + 861)]);
    __mv_vop1251 = _mm256_loadu_pd(&A[((i0 + 4) + 1664)]);
    __mv_vop1252 = _mm256_loadu_pd(&x[((i0 + 4) + 861)]);
    __mv_vop1958 = _mm256_loadu_pd(&y[((i0 + 0) + 862)]);
    __mv_vop1958 = _mm256_fmadd_pd(__mv_vop1248, __mv_vop1249, __mv_vop1958);
    _mm256_storeu_pd(&y[((i0 + 0) + 862)], __mv_vop1958);
    __mv_vop1959 = _mm256_loadu_pd(&y[((i0 + 4) + 862)]);
    __mv_vop1959 = _mm256_fmadd_pd(__mv_vop1251, __mv_vop1252, __mv_vop1959);
    _mm256_storeu_pd(&y[((i0 + 4) + 862)], __mv_vop1959);
    // y[1 * i0 + 862] += A[i0 + 1664] * x[1 * i0 + 861];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 862] += A[i0 + 1664] * x[1 * i0 + 861];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1254 = _mm256_loadu_pd(&A[((i0 + 0) + 1672)]);
    __mv_vop1255 = _mm256_loadu_pd(&x[((i0 + 0) + 870)]);
    __mv_vop1257 = _mm256_loadu_pd(&A[((i0 + 4) + 1672)]);
    __mv_vop1258 = _mm256_loadu_pd(&x[((i0 + 4) + 870)]);
    __mv_vop1960 = _mm256_loadu_pd(&y[((i0 + 0) + 869)]);
    __mv_vop1960 = _mm256_fmadd_pd(__mv_vop1254, __mv_vop1255, __mv_vop1960);
    _mm256_storeu_pd(&y[((i0 + 0) + 869)], __mv_vop1960);
    __mv_vop1961 = _mm256_loadu_pd(&y[((i0 + 4) + 869)]);
    __mv_vop1961 = _mm256_fmadd_pd(__mv_vop1257, __mv_vop1258, __mv_vop1961);
    _mm256_storeu_pd(&y[((i0 + 4) + 869)], __mv_vop1961);
    // y[1 * i0 + 869] += A[i0 + 1672] * x[1 * i0 + 870];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 869] += A[i0 + 1672] * x[1 * i0 + 870];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1260 = _mm256_loadu_pd(&A[((i0 + 0) + 1680)]);
    __mv_vop1261 = _mm256_loadu_pd(&x[((i0 + 0) + 869)]);
    __mv_vop1263 = _mm256_loadu_pd(&A[((i0 + 4) + 1680)]);
    __mv_vop1264 = _mm256_loadu_pd(&x[((i0 + 4) + 869)]);
    __mv_vop1962 = _mm256_loadu_pd(&y[((i0 + 0) + 870)]);
    __mv_vop1962 = _mm256_fmadd_pd(__mv_vop1260, __mv_vop1261, __mv_vop1962);
    _mm256_storeu_pd(&y[((i0 + 0) + 870)], __mv_vop1962);
    __mv_vop1963 = _mm256_loadu_pd(&y[((i0 + 4) + 870)]);
    __mv_vop1963 = _mm256_fmadd_pd(__mv_vop1263, __mv_vop1264, __mv_vop1963);
    _mm256_storeu_pd(&y[((i0 + 4) + 870)], __mv_vop1963);
    // y[1 * i0 + 870] += A[i0 + 1680] * x[1 * i0 + 869];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 870] += A[i0 + 1680] * x[1 * i0 + 869];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1266 = _mm256_loadu_pd(&A[((i0 + 0) + 1688)]);
    __mv_vop1267 = _mm256_loadu_pd(&x[((i0 + 0) + 878)]);
    __mv_vop1269 = _mm256_loadu_pd(&A[((i0 + 4) + 1688)]);
    __mv_vop1270 = _mm256_loadu_pd(&x[((i0 + 4) + 878)]);
    __mv_vop1964 = _mm256_loadu_pd(&y[((i0 + 0) + 877)]);
    __mv_vop1964 = _mm256_fmadd_pd(__mv_vop1266, __mv_vop1267, __mv_vop1964);
    _mm256_storeu_pd(&y[((i0 + 0) + 877)], __mv_vop1964);
    __mv_vop1965 = _mm256_loadu_pd(&y[((i0 + 4) + 877)]);
    __mv_vop1965 = _mm256_fmadd_pd(__mv_vop1269, __mv_vop1270, __mv_vop1965);
    _mm256_storeu_pd(&y[((i0 + 4) + 877)], __mv_vop1965);
    // y[1 * i0 + 877] += A[i0 + 1688] * x[1 * i0 + 878];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 877] += A[i0 + 1688] * x[1 * i0 + 878];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1272 = _mm256_loadu_pd(&A[((i0 + 0) + 1696)]);
    __mv_vop1273 = _mm256_loadu_pd(&x[((i0 + 0) + 877)]);
    __mv_vop1275 = _mm256_loadu_pd(&A[((i0 + 4) + 1696)]);
    __mv_vop1276 = _mm256_loadu_pd(&x[((i0 + 4) + 877)]);
    __mv_vop1966 = _mm256_loadu_pd(&y[((i0 + 0) + 878)]);
    __mv_vop1966 = _mm256_fmadd_pd(__mv_vop1272, __mv_vop1273, __mv_vop1966);
    _mm256_storeu_pd(&y[((i0 + 0) + 878)], __mv_vop1966);
    __mv_vop1967 = _mm256_loadu_pd(&y[((i0 + 4) + 878)]);
    __mv_vop1967 = _mm256_fmadd_pd(__mv_vop1275, __mv_vop1276, __mv_vop1967);
    _mm256_storeu_pd(&y[((i0 + 4) + 878)], __mv_vop1967);
    // y[1 * i0 + 878] += A[i0 + 1696] * x[1 * i0 + 877];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 878] += A[i0 + 1696] * x[1 * i0 + 877];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1278 = _mm256_loadu_pd(&A[((i0 + 0) + 1704)]);
    __mv_vop1279 = _mm256_loadu_pd(&x[((i0 + 0) + 886)]);
    __mv_vop1281 = _mm256_loadu_pd(&A[((i0 + 4) + 1704)]);
    __mv_vop1282 = _mm256_loadu_pd(&x[((i0 + 4) + 886)]);
    __mv_vop1968 = _mm256_loadu_pd(&y[((i0 + 0) + 885)]);
    __mv_vop1968 = _mm256_fmadd_pd(__mv_vop1278, __mv_vop1279, __mv_vop1968);
    _mm256_storeu_pd(&y[((i0 + 0) + 885)], __mv_vop1968);
    __mv_vop1969 = _mm256_loadu_pd(&y[((i0 + 4) + 885)]);
    __mv_vop1969 = _mm256_fmadd_pd(__mv_vop1281, __mv_vop1282, __mv_vop1969);
    _mm256_storeu_pd(&y[((i0 + 4) + 885)], __mv_vop1969);
    // y[1 * i0 + 885] += A[i0 + 1704] * x[1 * i0 + 886];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 885] += A[i0 + 1704] * x[1 * i0 + 886];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1284 = _mm256_loadu_pd(&A[((i0 + 0) + 1712)]);
    __mv_vop1285 = _mm256_loadu_pd(&x[((i0 + 0) + 885)]);
    __mv_vop1287 = _mm256_loadu_pd(&A[((i0 + 4) + 1712)]);
    __mv_vop1288 = _mm256_loadu_pd(&x[((i0 + 4) + 885)]);
    __mv_vop1970 = _mm256_loadu_pd(&y[((i0 + 0) + 886)]);
    __mv_vop1970 = _mm256_fmadd_pd(__mv_vop1284, __mv_vop1285, __mv_vop1970);
    _mm256_storeu_pd(&y[((i0 + 0) + 886)], __mv_vop1970);
    __mv_vop1971 = _mm256_loadu_pd(&y[((i0 + 4) + 886)]);
    __mv_vop1971 = _mm256_fmadd_pd(__mv_vop1287, __mv_vop1288, __mv_vop1971);
    _mm256_storeu_pd(&y[((i0 + 4) + 886)], __mv_vop1971);
    // y[1 * i0 + 886] += A[i0 + 1712] * x[1 * i0 + 885];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 886] += A[i0 + 1712] * x[1 * i0 + 885];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1290 = _mm256_loadu_pd(&A[((i0 + 0) + 1720)]);
    __mv_vop1291 = _mm256_loadu_pd(&x[((i0 + 0) + 894)]);
    __mv_vop1293 = _mm256_loadu_pd(&A[((i0 + 4) + 1720)]);
    __mv_vop1294 = _mm256_loadu_pd(&x[((i0 + 4) + 894)]);
    __mv_vop1972 = _mm256_loadu_pd(&y[((i0 + 0) + 893)]);
    __mv_vop1972 = _mm256_fmadd_pd(__mv_vop1290, __mv_vop1291, __mv_vop1972);
    _mm256_storeu_pd(&y[((i0 + 0) + 893)], __mv_vop1972);
    __mv_vop1973 = _mm256_loadu_pd(&y[((i0 + 4) + 893)]);
    __mv_vop1973 = _mm256_fmadd_pd(__mv_vop1293, __mv_vop1294, __mv_vop1973);
    _mm256_storeu_pd(&y[((i0 + 4) + 893)], __mv_vop1973);
    // y[1 * i0 + 893] += A[i0 + 1720] * x[1 * i0 + 894];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 893] += A[i0 + 1720] * x[1 * i0 + 894];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1296 = _mm256_loadu_pd(&A[((i0 + 0) + 1728)]);
    __mv_vop1297 = _mm256_loadu_pd(&x[((i0 + 0) + 893)]);
    __mv_vop1299 = _mm256_loadu_pd(&A[((i0 + 4) + 1728)]);
    __mv_vop1300 = _mm256_loadu_pd(&x[((i0 + 4) + 893)]);
    __mv_vop1974 = _mm256_loadu_pd(&y[((i0 + 0) + 894)]);
    __mv_vop1974 = _mm256_fmadd_pd(__mv_vop1296, __mv_vop1297, __mv_vop1974);
    _mm256_storeu_pd(&y[((i0 + 0) + 894)], __mv_vop1974);
    __mv_vop1975 = _mm256_loadu_pd(&y[((i0 + 4) + 894)]);
    __mv_vop1975 = _mm256_fmadd_pd(__mv_vop1299, __mv_vop1300, __mv_vop1975);
    _mm256_storeu_pd(&y[((i0 + 4) + 894)], __mv_vop1975);
    // y[1 * i0 + 894] += A[i0 + 1728] * x[1 * i0 + 893];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 894] += A[i0 + 1728] * x[1 * i0 + 893];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1302 = _mm256_loadu_pd(&A[((i0 + 0) + 1736)]);
    __mv_vop1303 = _mm256_loadu_pd(&x[((i0 + 0) + 902)]);
    __mv_vop1305 = _mm256_loadu_pd(&A[((i0 + 4) + 1736)]);
    __mv_vop1306 = _mm256_loadu_pd(&x[((i0 + 4) + 902)]);
    __mv_vop1976 = _mm256_loadu_pd(&y[((i0 + 0) + 901)]);
    __mv_vop1976 = _mm256_fmadd_pd(__mv_vop1302, __mv_vop1303, __mv_vop1976);
    _mm256_storeu_pd(&y[((i0 + 0) + 901)], __mv_vop1976);
    __mv_vop1977 = _mm256_loadu_pd(&y[((i0 + 4) + 901)]);
    __mv_vop1977 = _mm256_fmadd_pd(__mv_vop1305, __mv_vop1306, __mv_vop1977);
    _mm256_storeu_pd(&y[((i0 + 4) + 901)], __mv_vop1977);
    // y[1 * i0 + 901] += A[i0 + 1736] * x[1 * i0 + 902];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 901] += A[i0 + 1736] * x[1 * i0 + 902];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1308 = _mm256_loadu_pd(&A[((i0 + 0) + 1744)]);
    __mv_vop1309 = _mm256_loadu_pd(&x[((i0 + 0) + 901)]);
    __mv_vop1311 = _mm256_loadu_pd(&A[((i0 + 4) + 1744)]);
    __mv_vop1312 = _mm256_loadu_pd(&x[((i0 + 4) + 901)]);
    __mv_vop1978 = _mm256_loadu_pd(&y[((i0 + 0) + 902)]);
    __mv_vop1978 = _mm256_fmadd_pd(__mv_vop1308, __mv_vop1309, __mv_vop1978);
    _mm256_storeu_pd(&y[((i0 + 0) + 902)], __mv_vop1978);
    __mv_vop1979 = _mm256_loadu_pd(&y[((i0 + 4) + 902)]);
    __mv_vop1979 = _mm256_fmadd_pd(__mv_vop1311, __mv_vop1312, __mv_vop1979);
    _mm256_storeu_pd(&y[((i0 + 4) + 902)], __mv_vop1979);
    // y[1 * i0 + 902] += A[i0 + 1744] * x[1 * i0 + 901];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 902] += A[i0 + 1744] * x[1 * i0 + 901];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1314 = _mm256_loadu_pd(&A[((i0 + 0) + 1752)]);
    __mv_vop1315 = _mm256_loadu_pd(&x[((i0 + 0) + 910)]);
    __mv_vop1317 = _mm256_loadu_pd(&A[((i0 + 4) + 1752)]);
    __mv_vop1318 = _mm256_loadu_pd(&x[((i0 + 4) + 910)]);
    __mv_vop1980 = _mm256_loadu_pd(&y[((i0 + 0) + 909)]);
    __mv_vop1980 = _mm256_fmadd_pd(__mv_vop1314, __mv_vop1315, __mv_vop1980);
    _mm256_storeu_pd(&y[((i0 + 0) + 909)], __mv_vop1980);
    __mv_vop1981 = _mm256_loadu_pd(&y[((i0 + 4) + 909)]);
    __mv_vop1981 = _mm256_fmadd_pd(__mv_vop1317, __mv_vop1318, __mv_vop1981);
    _mm256_storeu_pd(&y[((i0 + 4) + 909)], __mv_vop1981);
    // y[1 * i0 + 909] += A[i0 + 1752] * x[1 * i0 + 910];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 909] += A[i0 + 1752] * x[1 * i0 + 910];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1320 = _mm256_loadu_pd(&A[((i0 + 0) + 1760)]);
    __mv_vop1321 = _mm256_loadu_pd(&x[((i0 + 0) + 909)]);
    __mv_vop1323 = _mm256_loadu_pd(&A[((i0 + 4) + 1760)]);
    __mv_vop1324 = _mm256_loadu_pd(&x[((i0 + 4) + 909)]);
    __mv_vop1982 = _mm256_loadu_pd(&y[((i0 + 0) + 910)]);
    __mv_vop1982 = _mm256_fmadd_pd(__mv_vop1320, __mv_vop1321, __mv_vop1982);
    _mm256_storeu_pd(&y[((i0 + 0) + 910)], __mv_vop1982);
    __mv_vop1983 = _mm256_loadu_pd(&y[((i0 + 4) + 910)]);
    __mv_vop1983 = _mm256_fmadd_pd(__mv_vop1323, __mv_vop1324, __mv_vop1983);
    _mm256_storeu_pd(&y[((i0 + 4) + 910)], __mv_vop1983);
    // y[1 * i0 + 910] += A[i0 + 1760] * x[1 * i0 + 909];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 910] += A[i0 + 1760] * x[1 * i0 + 909];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1326 = _mm256_loadu_pd(&A[((i0 + 0) + 1768)]);
    __mv_vop1327 = _mm256_loadu_pd(&x[((i0 + 0) + 918)]);
    __mv_vop1329 = _mm256_loadu_pd(&A[((i0 + 4) + 1768)]);
    __mv_vop1330 = _mm256_loadu_pd(&x[((i0 + 4) + 918)]);
    __mv_vop1984 = _mm256_loadu_pd(&y[((i0 + 0) + 917)]);
    __mv_vop1984 = _mm256_fmadd_pd(__mv_vop1326, __mv_vop1327, __mv_vop1984);
    _mm256_storeu_pd(&y[((i0 + 0) + 917)], __mv_vop1984);
    __mv_vop1985 = _mm256_loadu_pd(&y[((i0 + 4) + 917)]);
    __mv_vop1985 = _mm256_fmadd_pd(__mv_vop1329, __mv_vop1330, __mv_vop1985);
    _mm256_storeu_pd(&y[((i0 + 4) + 917)], __mv_vop1985);
    // y[1 * i0 + 917] += A[i0 + 1768] * x[1 * i0 + 918];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 917] += A[i0 + 1768] * x[1 * i0 + 918];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1332 = _mm256_loadu_pd(&A[((i0 + 0) + 1776)]);
    __mv_vop1333 = _mm256_loadu_pd(&x[((i0 + 0) + 917)]);
    __mv_vop1335 = _mm256_loadu_pd(&A[((i0 + 4) + 1776)]);
    __mv_vop1336 = _mm256_loadu_pd(&x[((i0 + 4) + 917)]);
    __mv_vop1986 = _mm256_loadu_pd(&y[((i0 + 0) + 918)]);
    __mv_vop1986 = _mm256_fmadd_pd(__mv_vop1332, __mv_vop1333, __mv_vop1986);
    _mm256_storeu_pd(&y[((i0 + 0) + 918)], __mv_vop1986);
    __mv_vop1987 = _mm256_loadu_pd(&y[((i0 + 4) + 918)]);
    __mv_vop1987 = _mm256_fmadd_pd(__mv_vop1335, __mv_vop1336, __mv_vop1987);
    _mm256_storeu_pd(&y[((i0 + 4) + 918)], __mv_vop1987);
    // y[1 * i0 + 918] += A[i0 + 1776] * x[1 * i0 + 917];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 918] += A[i0 + 1776] * x[1 * i0 + 917];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1338 = _mm256_loadu_pd(&A[((i0 + 0) + 1784)]);
    __mv_vop1339 = _mm256_loadu_pd(&x[((i0 + 0) + 926)]);
    __mv_vop1341 = _mm256_loadu_pd(&A[((i0 + 4) + 1784)]);
    __mv_vop1342 = _mm256_loadu_pd(&x[((i0 + 4) + 926)]);
    __mv_vop1988 = _mm256_loadu_pd(&y[((i0 + 0) + 925)]);
    __mv_vop1988 = _mm256_fmadd_pd(__mv_vop1338, __mv_vop1339, __mv_vop1988);
    _mm256_storeu_pd(&y[((i0 + 0) + 925)], __mv_vop1988);
    __mv_vop1989 = _mm256_loadu_pd(&y[((i0 + 4) + 925)]);
    __mv_vop1989 = _mm256_fmadd_pd(__mv_vop1341, __mv_vop1342, __mv_vop1989);
    _mm256_storeu_pd(&y[((i0 + 4) + 925)], __mv_vop1989);
    // y[1 * i0 + 925] += A[i0 + 1784] * x[1 * i0 + 926];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 925] += A[i0 + 1784] * x[1 * i0 + 926];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1344 = _mm256_loadu_pd(&A[((i0 + 0) + 1792)]);
    __mv_vop1345 = _mm256_loadu_pd(&x[((i0 + 0) + 925)]);
    __mv_vop1347 = _mm256_loadu_pd(&A[((i0 + 4) + 1792)]);
    __mv_vop1348 = _mm256_loadu_pd(&x[((i0 + 4) + 925)]);
    __mv_vop1990 = _mm256_loadu_pd(&y[((i0 + 0) + 926)]);
    __mv_vop1990 = _mm256_fmadd_pd(__mv_vop1344, __mv_vop1345, __mv_vop1990);
    _mm256_storeu_pd(&y[((i0 + 0) + 926)], __mv_vop1990);
    __mv_vop1991 = _mm256_loadu_pd(&y[((i0 + 4) + 926)]);
    __mv_vop1991 = _mm256_fmadd_pd(__mv_vop1347, __mv_vop1348, __mv_vop1991);
    _mm256_storeu_pd(&y[((i0 + 4) + 926)], __mv_vop1991);
    // y[1 * i0 + 926] += A[i0 + 1792] * x[1 * i0 + 925];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 926] += A[i0 + 1792] * x[1 * i0 + 925];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1350 = _mm256_loadu_pd(&A[((i0 + 0) + 1800)]);
    __mv_vop1351 = _mm256_loadu_pd(&x[((i0 + 0) + 934)]);
    __mv_vop1353 = _mm256_loadu_pd(&A[((i0 + 4) + 1800)]);
    __mv_vop1354 = _mm256_loadu_pd(&x[((i0 + 4) + 934)]);
    __mv_vop1992 = _mm256_loadu_pd(&y[((i0 + 0) + 933)]);
    __mv_vop1992 = _mm256_fmadd_pd(__mv_vop1350, __mv_vop1351, __mv_vop1992);
    _mm256_storeu_pd(&y[((i0 + 0) + 933)], __mv_vop1992);
    __mv_vop1993 = _mm256_loadu_pd(&y[((i0 + 4) + 933)]);
    __mv_vop1993 = _mm256_fmadd_pd(__mv_vop1353, __mv_vop1354, __mv_vop1993);
    _mm256_storeu_pd(&y[((i0 + 4) + 933)], __mv_vop1993);
    // y[1 * i0 + 933] += A[i0 + 1800] * x[1 * i0 + 934];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 933] += A[i0 + 1800] * x[1 * i0 + 934];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1356 = _mm256_loadu_pd(&A[((i0 + 0) + 1808)]);
    __mv_vop1357 = _mm256_loadu_pd(&x[((i0 + 0) + 933)]);
    __mv_vop1359 = _mm256_loadu_pd(&A[((i0 + 4) + 1808)]);
    __mv_vop1360 = _mm256_loadu_pd(&x[((i0 + 4) + 933)]);
    __mv_vop1994 = _mm256_loadu_pd(&y[((i0 + 0) + 934)]);
    __mv_vop1994 = _mm256_fmadd_pd(__mv_vop1356, __mv_vop1357, __mv_vop1994);
    _mm256_storeu_pd(&y[((i0 + 0) + 934)], __mv_vop1994);
    __mv_vop1995 = _mm256_loadu_pd(&y[((i0 + 4) + 934)]);
    __mv_vop1995 = _mm256_fmadd_pd(__mv_vop1359, __mv_vop1360, __mv_vop1995);
    _mm256_storeu_pd(&y[((i0 + 4) + 934)], __mv_vop1995);
    // y[1 * i0 + 934] += A[i0 + 1808] * x[1 * i0 + 933];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 934] += A[i0 + 1808] * x[1 * i0 + 933];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1362 = _mm256_loadu_pd(&A[((i0 + 0) + 1816)]);
    __mv_vop1363 = _mm256_loadu_pd(&x[((i0 + 0) + 942)]);
    __mv_vop1365 = _mm256_loadu_pd(&A[((i0 + 4) + 1816)]);
    __mv_vop1366 = _mm256_loadu_pd(&x[((i0 + 4) + 942)]);
    __mv_vop1996 = _mm256_loadu_pd(&y[((i0 + 0) + 941)]);
    __mv_vop1996 = _mm256_fmadd_pd(__mv_vop1362, __mv_vop1363, __mv_vop1996);
    _mm256_storeu_pd(&y[((i0 + 0) + 941)], __mv_vop1996);
    __mv_vop1997 = _mm256_loadu_pd(&y[((i0 + 4) + 941)]);
    __mv_vop1997 = _mm256_fmadd_pd(__mv_vop1365, __mv_vop1366, __mv_vop1997);
    _mm256_storeu_pd(&y[((i0 + 4) + 941)], __mv_vop1997);
    // y[1 * i0 + 941] += A[i0 + 1816] * x[1 * i0 + 942];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 941] += A[i0 + 1816] * x[1 * i0 + 942];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1368 = _mm256_loadu_pd(&A[((i0 + 0) + 1824)]);
    __mv_vop1369 = _mm256_loadu_pd(&x[((i0 + 0) + 941)]);
    __mv_vop1371 = _mm256_loadu_pd(&A[((i0 + 4) + 1824)]);
    __mv_vop1372 = _mm256_loadu_pd(&x[((i0 + 4) + 941)]);
    __mv_vop1998 = _mm256_loadu_pd(&y[((i0 + 0) + 942)]);
    __mv_vop1998 = _mm256_fmadd_pd(__mv_vop1368, __mv_vop1369, __mv_vop1998);
    _mm256_storeu_pd(&y[((i0 + 0) + 942)], __mv_vop1998);
    __mv_vop1999 = _mm256_loadu_pd(&y[((i0 + 4) + 942)]);
    __mv_vop1999 = _mm256_fmadd_pd(__mv_vop1371, __mv_vop1372, __mv_vop1999);
    _mm256_storeu_pd(&y[((i0 + 4) + 942)], __mv_vop1999);
    // y[1 * i0 + 942] += A[i0 + 1824] * x[1 * i0 + 941];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 942] += A[i0 + 1824] * x[1 * i0 + 941];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1374 = _mm256_loadu_pd(&A[((i0 + 0) + 1832)]);
    __mv_vop1375 = _mm256_loadu_pd(&x[((i0 + 0) + 950)]);
    __mv_vop1377 = _mm256_loadu_pd(&A[((i0 + 4) + 1832)]);
    __mv_vop1378 = _mm256_loadu_pd(&x[((i0 + 4) + 950)]);
    __mv_vop2000 = _mm256_loadu_pd(&y[((i0 + 0) + 949)]);
    __mv_vop2000 = _mm256_fmadd_pd(__mv_vop1374, __mv_vop1375, __mv_vop2000);
    _mm256_storeu_pd(&y[((i0 + 0) + 949)], __mv_vop2000);
    __mv_vop2001 = _mm256_loadu_pd(&y[((i0 + 4) + 949)]);
    __mv_vop2001 = _mm256_fmadd_pd(__mv_vop1377, __mv_vop1378, __mv_vop2001);
    _mm256_storeu_pd(&y[((i0 + 4) + 949)], __mv_vop2001);
    // y[1 * i0 + 949] += A[i0 + 1832] * x[1 * i0 + 950];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 949] += A[i0 + 1832] * x[1 * i0 + 950];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1380 = _mm256_loadu_pd(&A[((i0 + 0) + 1840)]);
    __mv_vop1381 = _mm256_loadu_pd(&x[((i0 + 0) + 949)]);
    __mv_vop1383 = _mm256_loadu_pd(&A[((i0 + 4) + 1840)]);
    __mv_vop1384 = _mm256_loadu_pd(&x[((i0 + 4) + 949)]);
    __mv_vop2002 = _mm256_loadu_pd(&y[((i0 + 0) + 950)]);
    __mv_vop2002 = _mm256_fmadd_pd(__mv_vop1380, __mv_vop1381, __mv_vop2002);
    _mm256_storeu_pd(&y[((i0 + 0) + 950)], __mv_vop2002);
    __mv_vop2003 = _mm256_loadu_pd(&y[((i0 + 4) + 950)]);
    __mv_vop2003 = _mm256_fmadd_pd(__mv_vop1383, __mv_vop1384, __mv_vop2003);
    _mm256_storeu_pd(&y[((i0 + 4) + 950)], __mv_vop2003);
    // y[1 * i0 + 950] += A[i0 + 1840] * x[1 * i0 + 949];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 950] += A[i0 + 1840] * x[1 * i0 + 949];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1386 = _mm256_loadu_pd(&A[((i0 + 0) + 1848)]);
    __mv_vop1387 = _mm256_loadu_pd(&x[((i0 + 0) + 958)]);
    __mv_vop1389 = _mm256_loadu_pd(&A[((i0 + 4) + 1848)]);
    __mv_vop1390 = _mm256_loadu_pd(&x[((i0 + 4) + 958)]);
    __mv_vop2004 = _mm256_loadu_pd(&y[((i0 + 0) + 957)]);
    __mv_vop2004 = _mm256_fmadd_pd(__mv_vop1386, __mv_vop1387, __mv_vop2004);
    _mm256_storeu_pd(&y[((i0 + 0) + 957)], __mv_vop2004);
    __mv_vop2005 = _mm256_loadu_pd(&y[((i0 + 4) + 957)]);
    __mv_vop2005 = _mm256_fmadd_pd(__mv_vop1389, __mv_vop1390, __mv_vop2005);
    _mm256_storeu_pd(&y[((i0 + 4) + 957)], __mv_vop2005);
    // y[1 * i0 + 957] += A[i0 + 1848] * x[1 * i0 + 958];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 957] += A[i0 + 1848] * x[1 * i0 + 958];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1392 = _mm256_loadu_pd(&A[((i0 + 0) + 1856)]);
    __mv_vop1393 = _mm256_loadu_pd(&x[((i0 + 0) + 957)]);
    __mv_vop1395 = _mm256_loadu_pd(&A[((i0 + 4) + 1856)]);
    __mv_vop1396 = _mm256_loadu_pd(&x[((i0 + 4) + 957)]);
    __mv_vop2006 = _mm256_loadu_pd(&y[((i0 + 0) + 958)]);
    __mv_vop2006 = _mm256_fmadd_pd(__mv_vop1392, __mv_vop1393, __mv_vop2006);
    _mm256_storeu_pd(&y[((i0 + 0) + 958)], __mv_vop2006);
    __mv_vop2007 = _mm256_loadu_pd(&y[((i0 + 4) + 958)]);
    __mv_vop2007 = _mm256_fmadd_pd(__mv_vop1395, __mv_vop1396, __mv_vop2007);
    _mm256_storeu_pd(&y[((i0 + 4) + 958)], __mv_vop2007);
    // y[1 * i0 + 958] += A[i0 + 1856] * x[1 * i0 + 957];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 958] += A[i0 + 1856] * x[1 * i0 + 957];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1398 = _mm256_loadu_pd(&A[((i0 + 0) + 1864)]);
    __mv_vop1399 = _mm256_loadu_pd(&x[((i0 + 0) + 974)]);
    __mv_vop1401 = _mm256_loadu_pd(&A[((i0 + 4) + 1864)]);
    __mv_vop1402 = _mm256_loadu_pd(&x[((i0 + 4) + 974)]);
    __mv_vop2008 = _mm256_loadu_pd(&y[((i0 + 0) + 973)]);
    __mv_vop2008 = _mm256_fmadd_pd(__mv_vop1398, __mv_vop1399, __mv_vop2008);
    _mm256_storeu_pd(&y[((i0 + 0) + 973)], __mv_vop2008);
    __mv_vop2009 = _mm256_loadu_pd(&y[((i0 + 4) + 973)]);
    __mv_vop2009 = _mm256_fmadd_pd(__mv_vop1401, __mv_vop1402, __mv_vop2009);
    _mm256_storeu_pd(&y[((i0 + 4) + 973)], __mv_vop2009);
    // y[1 * i0 + 973] += A[i0 + 1864] * x[1 * i0 + 974];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 973] += A[i0 + 1864] * x[1 * i0 + 974];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1404 = _mm256_loadu_pd(&A[((i0 + 0) + 1872)]);
    __mv_vop1405 = _mm256_loadu_pd(&x[((i0 + 0) + 973)]);
    __mv_vop1407 = _mm256_loadu_pd(&A[((i0 + 4) + 1872)]);
    __mv_vop1408 = _mm256_loadu_pd(&x[((i0 + 4) + 973)]);
    __mv_vop2010 = _mm256_loadu_pd(&y[((i0 + 0) + 974)]);
    __mv_vop2010 = _mm256_fmadd_pd(__mv_vop1404, __mv_vop1405, __mv_vop2010);
    _mm256_storeu_pd(&y[((i0 + 0) + 974)], __mv_vop2010);
    __mv_vop2011 = _mm256_loadu_pd(&y[((i0 + 4) + 974)]);
    __mv_vop2011 = _mm256_fmadd_pd(__mv_vop1407, __mv_vop1408, __mv_vop2011);
    _mm256_storeu_pd(&y[((i0 + 4) + 974)], __mv_vop2011);
    // y[1 * i0 + 974] += A[i0 + 1872] * x[1 * i0 + 973];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 974] += A[i0 + 1872] * x[1 * i0 + 973];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1410 = _mm256_loadu_pd(&A[((i0 + 0) + 1880)]);
    __mv_vop1411 = _mm256_loadu_pd(&x[((i0 + 0) + 982)]);
    __mv_vop1413 = _mm256_loadu_pd(&A[((i0 + 4) + 1880)]);
    __mv_vop1414 = _mm256_loadu_pd(&x[((i0 + 4) + 982)]);
    __mv_vop2012 = _mm256_loadu_pd(&y[((i0 + 0) + 981)]);
    __mv_vop2012 = _mm256_fmadd_pd(__mv_vop1410, __mv_vop1411, __mv_vop2012);
    _mm256_storeu_pd(&y[((i0 + 0) + 981)], __mv_vop2012);
    __mv_vop2013 = _mm256_loadu_pd(&y[((i0 + 4) + 981)]);
    __mv_vop2013 = _mm256_fmadd_pd(__mv_vop1413, __mv_vop1414, __mv_vop2013);
    _mm256_storeu_pd(&y[((i0 + 4) + 981)], __mv_vop2013);
    // y[1 * i0 + 981] += A[i0 + 1880] * x[1 * i0 + 982];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 981] += A[i0 + 1880] * x[1 * i0 + 982];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1416 = _mm256_loadu_pd(&A[((i0 + 0) + 1888)]);
    __mv_vop1417 = _mm256_loadu_pd(&x[((i0 + 0) + 981)]);
    __mv_vop1419 = _mm256_loadu_pd(&A[((i0 + 4) + 1888)]);
    __mv_vop1420 = _mm256_loadu_pd(&x[((i0 + 4) + 981)]);
    __mv_vop2014 = _mm256_loadu_pd(&y[((i0 + 0) + 982)]);
    __mv_vop2014 = _mm256_fmadd_pd(__mv_vop1416, __mv_vop1417, __mv_vop2014);
    _mm256_storeu_pd(&y[((i0 + 0) + 982)], __mv_vop2014);
    __mv_vop2015 = _mm256_loadu_pd(&y[((i0 + 4) + 982)]);
    __mv_vop2015 = _mm256_fmadd_pd(__mv_vop1419, __mv_vop1420, __mv_vop2015);
    _mm256_storeu_pd(&y[((i0 + 4) + 982)], __mv_vop2015);
    // y[1 * i0 + 982] += A[i0 + 1888] * x[1 * i0 + 981];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 982] += A[i0 + 1888] * x[1 * i0 + 981];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1422 = _mm256_loadu_pd(&A[((i0 + 0) + 1896)]);
    __mv_vop1423 = _mm256_loadu_pd(&x[((i0 + 0) + 990)]);
    __mv_vop1425 = _mm256_loadu_pd(&A[((i0 + 4) + 1896)]);
    __mv_vop1426 = _mm256_loadu_pd(&x[((i0 + 4) + 990)]);
    __mv_vop2016 = _mm256_loadu_pd(&y[((i0 + 0) + 989)]);
    __mv_vop2016 = _mm256_fmadd_pd(__mv_vop1422, __mv_vop1423, __mv_vop2016);
    _mm256_storeu_pd(&y[((i0 + 0) + 989)], __mv_vop2016);
    __mv_vop2017 = _mm256_loadu_pd(&y[((i0 + 4) + 989)]);
    __mv_vop2017 = _mm256_fmadd_pd(__mv_vop1425, __mv_vop1426, __mv_vop2017);
    _mm256_storeu_pd(&y[((i0 + 4) + 989)], __mv_vop2017);
    // y[1 * i0 + 989] += A[i0 + 1896] * x[1 * i0 + 990];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 989] += A[i0 + 1896] * x[1 * i0 + 990];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1428 = _mm256_loadu_pd(&A[((i0 + 0) + 1904)]);
    __mv_vop1429 = _mm256_loadu_pd(&x[((i0 + 0) + 989)]);
    __mv_vop1431 = _mm256_loadu_pd(&A[((i0 + 4) + 1904)]);
    __mv_vop1432 = _mm256_loadu_pd(&x[((i0 + 4) + 989)]);
    __mv_vop2018 = _mm256_loadu_pd(&y[((i0 + 0) + 990)]);
    __mv_vop2018 = _mm256_fmadd_pd(__mv_vop1428, __mv_vop1429, __mv_vop2018);
    _mm256_storeu_pd(&y[((i0 + 0) + 990)], __mv_vop2018);
    __mv_vop2019 = _mm256_loadu_pd(&y[((i0 + 4) + 990)]);
    __mv_vop2019 = _mm256_fmadd_pd(__mv_vop1431, __mv_vop1432, __mv_vop2019);
    _mm256_storeu_pd(&y[((i0 + 4) + 990)], __mv_vop2019);
    // y[1 * i0 + 990] += A[i0 + 1904] * x[1 * i0 + 989];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 990] += A[i0 + 1904] * x[1 * i0 + 989];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1434 = _mm256_loadu_pd(&A[((i0 + 0) + 1912)]);
    __mv_vop1435 = _mm256_loadu_pd(&x[((i0 + 0) + 998)]);
    __mv_vop1437 = _mm256_loadu_pd(&A[((i0 + 4) + 1912)]);
    __mv_vop1438 = _mm256_loadu_pd(&x[((i0 + 4) + 998)]);
    __mv_vop2020 = _mm256_loadu_pd(&y[((i0 + 0) + 997)]);
    __mv_vop2020 = _mm256_fmadd_pd(__mv_vop1434, __mv_vop1435, __mv_vop2020);
    _mm256_storeu_pd(&y[((i0 + 0) + 997)], __mv_vop2020);
    __mv_vop2021 = _mm256_loadu_pd(&y[((i0 + 4) + 997)]);
    __mv_vop2021 = _mm256_fmadd_pd(__mv_vop1437, __mv_vop1438, __mv_vop2021);
    _mm256_storeu_pd(&y[((i0 + 4) + 997)], __mv_vop2021);
    // y[1 * i0 + 997] += A[i0 + 1912] * x[1 * i0 + 998];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 997] += A[i0 + 1912] * x[1 * i0 + 998];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1440 = _mm256_loadu_pd(&A[((i0 + 0) + 1920)]);
    __mv_vop1441 = _mm256_loadu_pd(&x[((i0 + 0) + 997)]);
    __mv_vop1443 = _mm256_loadu_pd(&A[((i0 + 4) + 1920)]);
    __mv_vop1444 = _mm256_loadu_pd(&x[((i0 + 4) + 997)]);
    __mv_vop2022 = _mm256_loadu_pd(&y[((i0 + 0) + 998)]);
    __mv_vop2022 = _mm256_fmadd_pd(__mv_vop1440, __mv_vop1441, __mv_vop2022);
    _mm256_storeu_pd(&y[((i0 + 0) + 998)], __mv_vop2022);
    __mv_vop2023 = _mm256_loadu_pd(&y[((i0 + 4) + 998)]);
    __mv_vop2023 = _mm256_fmadd_pd(__mv_vop1443, __mv_vop1444, __mv_vop2023);
    _mm256_storeu_pd(&y[((i0 + 4) + 998)], __mv_vop2023);
    // y[1 * i0 + 998] += A[i0 + 1920] * x[1 * i0 + 997];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 998] += A[i0 + 1920] * x[1 * i0 + 997];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1446 = _mm256_loadu_pd(&A[((i0 + 0) + 1928)]);
    __mv_vop1447 = _mm256_loadu_pd(&x[((i0 + 0) + 1006)]);
    __mv_vop1449 = _mm256_loadu_pd(&A[((i0 + 4) + 1928)]);
    __mv_vop1450 = _mm256_loadu_pd(&x[((i0 + 4) + 1006)]);
    __mv_vop2024 = _mm256_loadu_pd(&y[((i0 + 0) + 1005)]);
    __mv_vop2024 = _mm256_fmadd_pd(__mv_vop1446, __mv_vop1447, __mv_vop2024);
    _mm256_storeu_pd(&y[((i0 + 0) + 1005)], __mv_vop2024);
    __mv_vop2025 = _mm256_loadu_pd(&y[((i0 + 4) + 1005)]);
    __mv_vop2025 = _mm256_fmadd_pd(__mv_vop1449, __mv_vop1450, __mv_vop2025);
    _mm256_storeu_pd(&y[((i0 + 4) + 1005)], __mv_vop2025);
    // y[1 * i0 + 1005] += A[i0 + 1928] * x[1 * i0 + 1006];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 1005] += A[i0 + 1928] * x[1 * i0 + 1006];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1452 = _mm256_loadu_pd(&A[((i0 + 0) + 1936)]);
    __mv_vop1453 = _mm256_loadu_pd(&x[((i0 + 0) + 1005)]);
    __mv_vop1455 = _mm256_loadu_pd(&A[((i0 + 4) + 1936)]);
    __mv_vop1456 = _mm256_loadu_pd(&x[((i0 + 4) + 1005)]);
    __mv_vop2026 = _mm256_loadu_pd(&y[((i0 + 0) + 1006)]);
    __mv_vop2026 = _mm256_fmadd_pd(__mv_vop1452, __mv_vop1453, __mv_vop2026);
    _mm256_storeu_pd(&y[((i0 + 0) + 1006)], __mv_vop2026);
    __mv_vop2027 = _mm256_loadu_pd(&y[((i0 + 4) + 1006)]);
    __mv_vop2027 = _mm256_fmadd_pd(__mv_vop1455, __mv_vop1456, __mv_vop2027);
    _mm256_storeu_pd(&y[((i0 + 4) + 1006)], __mv_vop2027);
    // y[1 * i0 + 1006] += A[i0 + 1936] * x[1 * i0 + 1005];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 1006] += A[i0 + 1936] * x[1 * i0 + 1005];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1458 = _mm256_loadu_pd(&A[((i0 + 0) + 1944)]);
    __mv_vop1459 = _mm256_loadu_pd(&x[((i0 + 0) + 1014)]);
    __mv_vop1461 = _mm256_loadu_pd(&A[((i0 + 4) + 1944)]);
    __mv_vop1462 = _mm256_loadu_pd(&x[((i0 + 4) + 1014)]);
    __mv_vop2028 = _mm256_loadu_pd(&y[((i0 + 0) + 1013)]);
    __mv_vop2028 = _mm256_fmadd_pd(__mv_vop1458, __mv_vop1459, __mv_vop2028);
    _mm256_storeu_pd(&y[((i0 + 0) + 1013)], __mv_vop2028);
    __mv_vop2029 = _mm256_loadu_pd(&y[((i0 + 4) + 1013)]);
    __mv_vop2029 = _mm256_fmadd_pd(__mv_vop1461, __mv_vop1462, __mv_vop2029);
    _mm256_storeu_pd(&y[((i0 + 4) + 1013)], __mv_vop2029);
    // y[1 * i0 + 1013] += A[i0 + 1944] * x[1 * i0 + 1014];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 1013] += A[i0 + 1944] * x[1 * i0 + 1014];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1464 = _mm256_loadu_pd(&A[((i0 + 0) + 1952)]);
    __mv_vop1465 = _mm256_loadu_pd(&x[((i0 + 0) + 1013)]);
    __mv_vop1467 = _mm256_loadu_pd(&A[((i0 + 4) + 1952)]);
    __mv_vop1468 = _mm256_loadu_pd(&x[((i0 + 4) + 1013)]);
    __mv_vop2030 = _mm256_loadu_pd(&y[((i0 + 0) + 1014)]);
    __mv_vop2030 = _mm256_fmadd_pd(__mv_vop1464, __mv_vop1465, __mv_vop2030);
    _mm256_storeu_pd(&y[((i0 + 0) + 1014)], __mv_vop2030);
    __mv_vop2031 = _mm256_loadu_pd(&y[((i0 + 4) + 1014)]);
    __mv_vop2031 = _mm256_fmadd_pd(__mv_vop1467, __mv_vop1468, __mv_vop2031);
    _mm256_storeu_pd(&y[((i0 + 4) + 1014)], __mv_vop2031);
    // y[1 * i0 + 1014] += A[i0 + 1952] * x[1 * i0 + 1013];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 1014] += A[i0 + 1952] * x[1 * i0 + 1013];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1470 = _mm256_loadu_pd(&A[((i0 + 0) + 1960)]);
    __mv_vop1471 = _mm256_loadu_pd(&x[((i0 + 0) + 1022)]);
    __mv_vop1473 = _mm256_loadu_pd(&A[((i0 + 4) + 1960)]);
    __mv_vop1474 = _mm256_loadu_pd(&x[((i0 + 4) + 1022)]);
    __mv_vop2032 = _mm256_loadu_pd(&y[((i0 + 0) + 1021)]);
    __mv_vop2032 = _mm256_fmadd_pd(__mv_vop1470, __mv_vop1471, __mv_vop2032);
    _mm256_storeu_pd(&y[((i0 + 0) + 1021)], __mv_vop2032);
    __mv_vop2033 = _mm256_loadu_pd(&y[((i0 + 4) + 1021)]);
    __mv_vop2033 = _mm256_fmadd_pd(__mv_vop1473, __mv_vop1474, __mv_vop2033);
    _mm256_storeu_pd(&y[((i0 + 4) + 1021)], __mv_vop2033);
    // y[1 * i0 + 1021] += A[i0 + 1960] * x[1 * i0 + 1022];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 1021] += A[i0 + 1960] * x[1 * i0 + 1022];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1476 = _mm256_loadu_pd(&A[((i0 + 0) + 1968)]);
    __mv_vop1477 = _mm256_loadu_pd(&x[((i0 + 0) + 1021)]);
    __mv_vop1479 = _mm256_loadu_pd(&A[((i0 + 4) + 1968)]);
    __mv_vop1480 = _mm256_loadu_pd(&x[((i0 + 4) + 1021)]);
    __mv_vop2034 = _mm256_loadu_pd(&y[((i0 + 0) + 1022)]);
    __mv_vop2034 = _mm256_fmadd_pd(__mv_vop1476, __mv_vop1477, __mv_vop2034);
    _mm256_storeu_pd(&y[((i0 + 0) + 1022)], __mv_vop2034);
    __mv_vop2035 = _mm256_loadu_pd(&y[((i0 + 4) + 1022)]);
    __mv_vop2035 = _mm256_fmadd_pd(__mv_vop1479, __mv_vop1480, __mv_vop2035);
    _mm256_storeu_pd(&y[((i0 + 4) + 1022)], __mv_vop2035);
    // y[1 * i0 + 1022] += A[i0 + 1968] * x[1 * i0 + 1021];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 1022] += A[i0 + 1968] * x[1 * i0 + 1021];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1482 = _mm256_loadu_pd(&A[((i0 + 0) + 1976)]);
    __mv_vop1483 = _mm256_loadu_pd(&x[((i0 + 0) + 1030)]);
    __mv_vop1485 = _mm256_loadu_pd(&A[((i0 + 4) + 1976)]);
    __mv_vop1486 = _mm256_loadu_pd(&x[((i0 + 4) + 1030)]);
    __mv_vop2036 = _mm256_loadu_pd(&y[((i0 + 0) + 1029)]);
    __mv_vop2036 = _mm256_fmadd_pd(__mv_vop1482, __mv_vop1483, __mv_vop2036);
    _mm256_storeu_pd(&y[((i0 + 0) + 1029)], __mv_vop2036);
    __mv_vop2037 = _mm256_loadu_pd(&y[((i0 + 4) + 1029)]);
    __mv_vop2037 = _mm256_fmadd_pd(__mv_vop1485, __mv_vop1486, __mv_vop2037);
    _mm256_storeu_pd(&y[((i0 + 4) + 1029)], __mv_vop2037);
    // y[1 * i0 + 1029] += A[i0 + 1976] * x[1 * i0 + 1030];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 1029] += A[i0 + 1976] * x[1 * i0 + 1030];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1488 = _mm256_loadu_pd(&A[((i0 + 0) + 1984)]);
    __mv_vop1489 = _mm256_loadu_pd(&x[((i0 + 0) + 1029)]);
    __mv_vop1491 = _mm256_loadu_pd(&A[((i0 + 4) + 1984)]);
    __mv_vop1492 = _mm256_loadu_pd(&x[((i0 + 4) + 1029)]);
    __mv_vop2038 = _mm256_loadu_pd(&y[((i0 + 0) + 1030)]);
    __mv_vop2038 = _mm256_fmadd_pd(__mv_vop1488, __mv_vop1489, __mv_vop2038);
    _mm256_storeu_pd(&y[((i0 + 0) + 1030)], __mv_vop2038);
    __mv_vop2039 = _mm256_loadu_pd(&y[((i0 + 4) + 1030)]);
    __mv_vop2039 = _mm256_fmadd_pd(__mv_vop1491, __mv_vop1492, __mv_vop2039);
    _mm256_storeu_pd(&y[((i0 + 4) + 1030)], __mv_vop2039);
    // y[1 * i0 + 1030] += A[i0 + 1984] * x[1 * i0 + 1029];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 1030] += A[i0 + 1984] * x[1 * i0 + 1029];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1494 = _mm256_loadu_pd(&A[((i0 + 0) + 1992)]);
    __mv_vop1495 = _mm256_loadu_pd(&x[((i0 + 0) + 1038)]);
    __mv_vop1497 = _mm256_loadu_pd(&A[((i0 + 4) + 1992)]);
    __mv_vop1498 = _mm256_loadu_pd(&x[((i0 + 4) + 1038)]);
    __mv_vop2040 = _mm256_loadu_pd(&y[((i0 + 0) + 1037)]);
    __mv_vop2040 = _mm256_fmadd_pd(__mv_vop1494, __mv_vop1495, __mv_vop2040);
    _mm256_storeu_pd(&y[((i0 + 0) + 1037)], __mv_vop2040);
    __mv_vop2041 = _mm256_loadu_pd(&y[((i0 + 4) + 1037)]);
    __mv_vop2041 = _mm256_fmadd_pd(__mv_vop1497, __mv_vop1498, __mv_vop2041);
    _mm256_storeu_pd(&y[((i0 + 4) + 1037)], __mv_vop2041);
    // y[1 * i0 + 1037] += A[i0 + 1992] * x[1 * i0 + 1038];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 1037] += A[i0 + 1992] * x[1 * i0 + 1038];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1500 = _mm256_loadu_pd(&A[((i0 + 0) + 2000)]);
    __mv_vop1501 = _mm256_loadu_pd(&x[((i0 + 0) + 1037)]);
    __mv_vop1503 = _mm256_loadu_pd(&A[((i0 + 4) + 2000)]);
    __mv_vop1504 = _mm256_loadu_pd(&x[((i0 + 4) + 1037)]);
    __mv_vop2042 = _mm256_loadu_pd(&y[((i0 + 0) + 1038)]);
    __mv_vop2042 = _mm256_fmadd_pd(__mv_vop1500, __mv_vop1501, __mv_vop2042);
    _mm256_storeu_pd(&y[((i0 + 0) + 1038)], __mv_vop2042);
    __mv_vop2043 = _mm256_loadu_pd(&y[((i0 + 4) + 1038)]);
    __mv_vop2043 = _mm256_fmadd_pd(__mv_vop1503, __mv_vop1504, __mv_vop2043);
    _mm256_storeu_pd(&y[((i0 + 4) + 1038)], __mv_vop2043);
    // y[1 * i0 + 1038] += A[i0 + 2000] * x[1 * i0 + 1037];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 1038] += A[i0 + 2000] * x[1 * i0 + 1037];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1506 = _mm256_loadu_pd(&A[((i0 + 0) + 2008)]);
    __mv_vop1507 = _mm256_loadu_pd(&x[((i0 + 0) + 1046)]);
    __mv_vop1509 = _mm256_loadu_pd(&A[((i0 + 4) + 2008)]);
    __mv_vop1510 = _mm256_loadu_pd(&x[((i0 + 4) + 1046)]);
    __mv_vop2044 = _mm256_loadu_pd(&y[((i0 + 0) + 1045)]);
    __mv_vop2044 = _mm256_fmadd_pd(__mv_vop1506, __mv_vop1507, __mv_vop2044);
    _mm256_storeu_pd(&y[((i0 + 0) + 1045)], __mv_vop2044);
    __mv_vop2045 = _mm256_loadu_pd(&y[((i0 + 4) + 1045)]);
    __mv_vop2045 = _mm256_fmadd_pd(__mv_vop1509, __mv_vop1510, __mv_vop2045);
    _mm256_storeu_pd(&y[((i0 + 4) + 1045)], __mv_vop2045);
    // y[1 * i0 + 1045] += A[i0 + 2008] * x[1 * i0 + 1046];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 1045] += A[i0 + 2008] * x[1 * i0 + 1046];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1512 = _mm256_loadu_pd(&A[((i0 + 0) + 2016)]);
    __mv_vop1513 = _mm256_loadu_pd(&x[((i0 + 0) + 1045)]);
    __mv_vop1515 = _mm256_loadu_pd(&A[((i0 + 4) + 2016)]);
    __mv_vop1516 = _mm256_loadu_pd(&x[((i0 + 4) + 1045)]);
    __mv_vop2046 = _mm256_loadu_pd(&y[((i0 + 0) + 1046)]);
    __mv_vop2046 = _mm256_fmadd_pd(__mv_vop1512, __mv_vop1513, __mv_vop2046);
    _mm256_storeu_pd(&y[((i0 + 0) + 1046)], __mv_vop2046);
    __mv_vop2047 = _mm256_loadu_pd(&y[((i0 + 4) + 1046)]);
    __mv_vop2047 = _mm256_fmadd_pd(__mv_vop1515, __mv_vop1516, __mv_vop2047);
    _mm256_storeu_pd(&y[((i0 + 4) + 1046)], __mv_vop2047);
    // y[1 * i0 + 1046] += A[i0 + 2016] * x[1 * i0 + 1045];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 1046] += A[i0 + 2016] * x[1 * i0 + 1045];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1518 = _mm256_loadu_pd(&A[((i0 + 0) + 2024)]);
    __mv_vop1519 = _mm256_loadu_pd(&x[((i0 + 0) + 1054)]);
    __mv_vop1521 = _mm256_loadu_pd(&A[((i0 + 4) + 2024)]);
    __mv_vop1522 = _mm256_loadu_pd(&x[((i0 + 4) + 1054)]);
    __mv_vop2048 = _mm256_loadu_pd(&y[((i0 + 0) + 1053)]);
    __mv_vop2048 = _mm256_fmadd_pd(__mv_vop1518, __mv_vop1519, __mv_vop2048);
    _mm256_storeu_pd(&y[((i0 + 0) + 1053)], __mv_vop2048);
    __mv_vop2049 = _mm256_loadu_pd(&y[((i0 + 4) + 1053)]);
    __mv_vop2049 = _mm256_fmadd_pd(__mv_vop1521, __mv_vop1522, __mv_vop2049);
    _mm256_storeu_pd(&y[((i0 + 4) + 1053)], __mv_vop2049);
    // y[1 * i0 + 1053] += A[i0 + 2024] * x[1 * i0 + 1054];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 1053] += A[i0 + 2024] * x[1 * i0 + 1054];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1524 = _mm256_loadu_pd(&A[((i0 + 0) + 2032)]);
    __mv_vop1525 = _mm256_loadu_pd(&x[((i0 + 0) + 1053)]);
    __mv_vop1527 = _mm256_loadu_pd(&A[((i0 + 4) + 2032)]);
    __mv_vop1528 = _mm256_loadu_pd(&x[((i0 + 4) + 1053)]);
    __mv_vop2050 = _mm256_loadu_pd(&y[((i0 + 0) + 1054)]);
    __mv_vop2050 = _mm256_fmadd_pd(__mv_vop1524, __mv_vop1525, __mv_vop2050);
    _mm256_storeu_pd(&y[((i0 + 0) + 1054)], __mv_vop2050);
    __mv_vop2051 = _mm256_loadu_pd(&y[((i0 + 4) + 1054)]);
    __mv_vop2051 = _mm256_fmadd_pd(__mv_vop1527, __mv_vop1528, __mv_vop2051);
    _mm256_storeu_pd(&y[((i0 + 4) + 1054)], __mv_vop2051);
    // y[1 * i0 + 1054] += A[i0 + 2032] * x[1 * i0 + 1053];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 1054] += A[i0 + 2032] * x[1 * i0 + 1053];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1530 = _mm256_loadu_pd(&A[((i0 + 0) + 2040)]);
    __mv_vop1531 = _mm256_loadu_pd(&x[((i0 + 0) + 1062)]);
    __mv_vop1533 = _mm256_loadu_pd(&A[((i0 + 4) + 2040)]);
    __mv_vop1534 = _mm256_loadu_pd(&x[((i0 + 4) + 1062)]);
    __mv_vop2052 = _mm256_loadu_pd(&y[((i0 + 0) + 1061)]);
    __mv_vop2052 = _mm256_fmadd_pd(__mv_vop1530, __mv_vop1531, __mv_vop2052);
    _mm256_storeu_pd(&y[((i0 + 0) + 1061)], __mv_vop2052);
    __mv_vop2053 = _mm256_loadu_pd(&y[((i0 + 4) + 1061)]);
    __mv_vop2053 = _mm256_fmadd_pd(__mv_vop1533, __mv_vop1534, __mv_vop2053);
    _mm256_storeu_pd(&y[((i0 + 4) + 1061)], __mv_vop2053);
    // y[1 * i0 + 1061] += A[i0 + 2040] * x[1 * i0 + 1062];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 1061] += A[i0 + 2040] * x[1 * i0 + 1062];
  }

  for (i0 = 0; (i0 + 8) <= 7; i0 += 8) {
    __mv_vop1536 = _mm256_loadu_pd(&A[((i0 + 0) + 2048)]);
    __mv_vop1537 = _mm256_loadu_pd(&x[((i0 + 0) + 1061)]);
    __mv_vop1539 = _mm256_loadu_pd(&A[((i0 + 4) + 2048)]);
    __mv_vop1540 = _mm256_loadu_pd(&x[((i0 + 4) + 1061)]);
    __mv_vop2054 = _mm256_loadu_pd(&y[((i0 + 0) + 1062)]);
    __mv_vop2054 = _mm256_fmadd_pd(__mv_vop1536, __mv_vop1537, __mv_vop2054);
    _mm256_storeu_pd(&y[((i0 + 0) + 1062)], __mv_vop2054);
    __mv_vop2055 = _mm256_loadu_pd(&y[((i0 + 4) + 1062)]);
    __mv_vop2055 = _mm256_fmadd_pd(__mv_vop1539, __mv_vop1540, __mv_vop2055);
    _mm256_storeu_pd(&y[((i0 + 4) + 1062)], __mv_vop2055);
    // y[1 * i0 + 1062] += A[i0 + 2048] * x[1 * i0 + 1061];
  }
  for (i0 = i0; i0 < 7; i0 += 1) {
    y[1 * i0 + 1062] += A[i0 + 2048] * x[1 * i0 + 1061];
  }

#pragma endmacveth
}
